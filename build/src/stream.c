/*
 * Copyright (c) 2021 Colin Jensen.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <rtsisp.h>
#include <rtscamkit.h>
#include <rtsavapi.h>
#include <rtsvideo.h>
#include <rts_pthreadpool.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <rts_io_adc.h>
#include <sys/resource.h>

#define FIFO_NAME_HIGH "/tmp/h264_high_fifo"
//#define DOMAIN_GPIO_MCU    1
//#define GPIO_ANODE 20
//#define GPIO_CATHODE 21

int isp = -1;
static int g_exit;
int night = 3;
int arg_amount = 0;

static void Termination(int sign) {
    g_exit = 1;
}

int set_video_CVBR_mode(int h264_ch) {
    struct rts_video_h264_ctrl *h264_ctl = NULL;
    int ret;

    ret = rts_av_query_h264_ctrl(h264_ch, &h264_ctl);
    if (h264_ctl == NULL)
        return -1;
    rts_av_get_h264_ctrl(h264_ctl);

    if (!ret) {
        h264_ctl->bitrate_mode = RTS_BITRATE_MODE_C_VBR;

//        h264_ctl->max_bitrate = 2 * 1024 * 1024;
        h264_ctl->max_bitrate = (5 * 1024 * 100) * 2;
        h264_ctl->min_bitrate = h264_ctl->max_bitrate / 2;

        fprintf(stdout, "set H264 to CVBR mode.\n");
        rts_av_set_h264_ctrl(h264_ctl);
        rts_av_release_h264_ctrl(h264_ctl);
    }

    return 0;
}

static int get_valid_value(int id, int value, struct rts_video_control *ctrl) {
    int tvalue = value;

    if (value < ctrl->minimum)
        tvalue = ctrl->minimum;
    if (value > ctrl->maximum)
        tvalue = ctrl->maximum;
    if ((value - ctrl->minimum) % ctrl->step)
        tvalue = value - (value - ctrl->minimum) % ctrl->step;

    return tvalue;
}

int manage_ir_cut(int action) {
//    int soc = rts_isp_ctrl_open();
//
//    enum rts_isp_gpio_value anode, cathode;
//    rts_isp_request_gpio(soc, GPIO_ANODE);
//    rts_isp_request_gpio(soc, GPIO_CATHODE);
//    rts_isp_set_gpio_direction(soc, GPIO_ANODE, RTS_ISP_GPIO_OUTPUT);
//    rts_isp_set_gpio_direction(soc, GPIO_CATHODE, RTS_ISP_GPIO_OUTPUT);
//
//    rts_isp_get_gpio_value(soc, GPIO_ANODE, &anode);
//    rts_isp_get_gpio_value(soc, GPIO_CATHODE, &cathode);
//    if (action == 1) {
//        rts_isp_set_gpio_value(soc, GPIO_ANODE, RTS_ISP_GPIO_HIGH);
//        rts_isp_set_gpio_value(soc, GPIO_CATHODE, RTS_ISP_GPIO_LOW);
//    } else {
//        rts_isp_set_gpio_value(soc, GPIO_ANODE, RTS_ISP_GPIO_LOW);
//        rts_isp_set_gpio_value(soc, GPIO_CATHODE, RTS_ISP_GPIO_HIGH);
//    }
//    rts_isp_free_gpio(soc, GPIO_ANODE);
//    rts_isp_free_gpio(soc, GPIO_CATHODE);
//    rts_isp_ctrl_close(soc);

    int driver = open("/dev/cpld_periph", O_RDWR);
    if (action == 0) {
        ioctl(driver, _IOC(_IOC_NONE, 0x70, 0x15, 0), 0);
    } else {
        ioctl(driver, _IOC(_IOC_NONE, 0x70, 0x16, 0), 0);
    }
    close(driver);

}

int manage_modes(enum enum_rts_video_ctrl_id type, int value) {
    struct rts_video_control ctrl;
    int ret;
    ret = rts_av_get_isp_ctrl(type, &ctrl);
    if (ret) {
        RTS_ERR("Failed to change GPIO: ret = %d for %d\n", ret, type);
        return 0;
    }
    int map_value = get_valid_value(type, value, &ctrl);
    if (ctrl.current_value == map_value) {
        return 0;
    }
    ctrl.current_value = value;
    ret = rts_av_set_isp_ctrl(type, &ctrl);
    if (ret) {
        RTS_ERR("Failed to set new value\n", ret);
        return 0;
    }

    return 1;
}

static void day_mode_or_night_mode() {
    // We need to read the ADC (Light Sensor) first
    int adc_value;
    adc_value = rts_io_adc_get_value(ADC_CHANNEL_0);
    int detected_night = 0;
    int sensor_sensitivity = 2000;
    if (arg_amount > 1) {
        // Inverted light detection logic provided
        if (adc_value > sensor_sensitivity) {
            detected_night = 0;
        } else {
            detected_night = 1;
        }
    } else {
        if (adc_value > sensor_sensitivity) {
            detected_night = 1;
        } else {
            detected_night = 0;
        }
    }
    // We have detected darkness
    // We store the state of the camera's current nightmode in night
    if (night != 1 && detected_night == 1) {
        manage_modes(RTS_VIDEO_CTRL_ID_GRAY_MODE, 1);
        manage_modes(RTS_VIDEO_CTRL_ID_IR_MODE, 2);
        manage_ir_cut(1);
        night = 1;
    } else if (night != 0 && detected_night == 0) {
        // We have detected light
        manage_modes(RTS_VIDEO_CTRL_ID_GRAY_MODE, 0);
        manage_modes(RTS_VIDEO_CTRL_ID_IR_MODE, 0);
        manage_ir_cut(0);
        night = 0;
    }
}


static void isp_ctrl() {
    RTS_INFO("Control thread started\n");
    while (!g_exit) {
        day_mode_or_night_mode();
        sleep(3);

    }

    RTS_INFO("quit isp control thread\n");
}

int start_stream() {
    struct rts_isp_attr isp_attr;
    struct rts_h264_attr h264_attr;
    struct rts_av_profile profile;

    PthreadPool tpool = NULL;

    FILE *pfile = NULL;
    uint32_t number = 0;
    int h264 = -1;
    int ret;
    struct timeval begin, end;
    unsigned long delta;

    isp_attr.isp_id = 0;
    isp_attr.isp_buf_num = 3;
    isp = rts_av_create_isp_chn(&isp_attr);

    if (isp < 0) {
        RTS_ERR("fail to create isp chn, ret = %d\n", isp);
        ret = RTS_RETURN(RTS_E_OPEN_FAIL);
        goto exit;
    }
    RTS_INFO("isp chn : %d\n", isp);

    profile.fmt = RTS_V_FMT_YUV420SEMIPLANAR;
    profile.video.width = 1920;
    profile.video.height = 1080;
//    profile.video.width = 1280;
//    profile.video.height = 720;
    profile.video.numerator = 1;
    profile.video.denominator = 20;

    ret = rts_av_set_profile(isp, &profile);
    if (ret) {
        RTS_ERR("set isp profile fail, ret = %d\n", ret);
        goto exit;
    }
    h264_attr.level = H264_LEVEL_4;
    h264_attr.qp = -1;
    h264_attr.bps = (5 * 1024 * 100) * 2;
    h264_attr.gop = 30;
    h264_attr.videostab = 1;
    h264_attr.rotation = RTS_AV_ROTATION_0;
    h264 = rts_av_create_h264_chn(&h264_attr);
    if (h264 < 0) {
        RTS_ERR("fail to create h264 chn, ret = %d\n", h264);
        ret = RTS_RETURN(RTS_E_OPEN_FAIL);
        goto exit;
    }
    RTS_INFO("h264 chn : %d\n", h264);

    ret = rts_av_bind(isp, h264);
    if (ret) {
        RTS_ERR("fail to bind isp and h264, ret %d\n", ret);
        goto exit;
    }
    rts_av_enable_chn(isp);
    rts_av_enable_chn(h264);
    manage_modes(RTS_VIDEO_CTRL_ID_NOISE_REDUCTION, 100);
    manage_modes(RTS_VIDEO_CTRL_ID_LDC, 1);
//    manage_modes(RTS_VIDEO_CTRL_ID_FOCUS, 100);
    manage_modes(RTS_VIDEO_CTRL_ID_DETAIL_ENHANCEMENT, 100);
    manage_modes(RTS_VIDEO_CTRL_ID_3DNR, -1);
    tpool = rts_pthreadpool_init(1);
    if (!tpool) {
        ret = -1;
        goto exit;
    }
    rts_pthreadpool_add_task(tpool, isp_ctrl, NULL, NULL);
    set_video_CVBR_mode(h264);
    rts_av_start_recv(h264);

    FILE *fd;
    unlink(FIFO_NAME_HIGH);
    if (mkfifo(FIFO_NAME_HIGH, 0755) < 0) {
        RTS_INFO("Failed to create fifo file\n");
        goto exit;
    }


    fd = fopen(FIFO_NAME_HIGH, "wb");
    if (!fd) {
        RTS_INFO("Failed to open fifo file\n");
        goto exit;
    }

    signal(SIGPIPE, SIG_IGN);


    // Try load the V4L device
    int vfd;
    vfd = rts_isp_v4l2_open(isp_attr.isp_id);
    if (vfd > 0) {
        RTS_INFO("Opened the V4L2 fd\n");

        rts_isp_v4l2_close(vfd);
    }
    manage_ir_cut(1); // Always start as if it was day time
    while (!g_exit) {

        struct rts_av_buffer *buffer = NULL;

        if (rts_av_poll(h264)) {
            usleep(1000);
            continue;
        }
        if (rts_av_recv(h264, &buffer)) {
            usleep(1000);
            continue;
        }
        if (buffer) {
            if (buffer->flags & RTSTREAM_PKT_FLAG_KEY) {
                fprintf(stdout, "Frame %d\n", number);
            }
            //RTS_INFO("Address %p", buffer->vm_addr);
            //RTS_INFO("Bytes Used %d", buffer->bytesused);
            //RTS_INFO("Physical Address %p", buffer->phy_addr);
            //RTS_INFO("Length Used %d", buffer->length);
            //RTS_INFO("Buffer Header Address %p", &buffer);
            //RTS_INFO("H264 Control Address %p", &h264);
            if (fwrite(buffer->vm_addr, 1, buffer->bytesused, fd) != buffer->bytesused) {
                fprintf(stdout, "Possible SIGPIPE break from stream disconnection, skipping flush\n");
            } else {
                fflush(fd);
            }
            number++;
            rts_av_put_buffer(buffer);
            buffer = NULL;
        }
    }

    rts_av_disable_chn(isp);
    rts_av_disable_chn(h264);

    RTS_SAFE_RELEASE(pfile, fclose);

    RTS_INFO("\n");
    RTS_INFO("get %d frames\n", number);
    exit:

    RTS_SAFE_RELEASE(tpool, rts_pthreadpool_destroy);
    if (isp >= 0) {
        rts_av_destroy_chn(isp);
        isp = -1;
    }
    if (h264 >= 0) {
        rts_av_destroy_chn(h264);
        h264 = -1;
    }
    fclose(fd);

    return ret;
}

int main(int argc, char *argv[]) {
    int ret = 0;
    arg_amount = argc;
    int which = PRIO_PROCESS;
    id_t pid;
    int priority = -5;

    pid = getpid();
    setpriority(which, pid, priority);
    signal(SIGINT, Termination);
    signal(SIGTERM, Termination);


    ret = rts_av_init();
    if (ret) {
        RTS_ERR("rts_av_init fail\n");
        return ret;
    }
    start_stream();

    rts_av_release();
    return 0;
}
