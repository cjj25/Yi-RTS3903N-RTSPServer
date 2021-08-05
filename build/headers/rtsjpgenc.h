/*
 * Realtek Semiconductor Corp.
 *
 * libs/include/rtsjpeg.h
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTSJPGENC_H
#define _RTSJPGENC_H
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef const void *RtsJpgEncInst;

enum rtsjpgenc_picture_type {
	RTSJPGENC_YUV420_SEMIPLANAR = 0,
	RTSJPGENC_YUV422_SEMIPLANAR
};

enum rtsjpgenc_rotation {
	RTSJPGENC_ROTATE_0 = 0,
	RTSJPGENC_ROTATE_90R = 2, /*rotate 90 degrees clockwise*/
	RTSJPGENC_ROTATE_90L = 3, /*rotate 90 degrees counter-clockwise*/
};

struct rtsjpgenc_config {
	enum rtsjpgenc_picture_type input_type;
	enum rtsjpgenc_rotation rotation;
	uint16_t width;
	uint16_t height;
};

struct rtsjpgenc_coding_ctrl {
	uint16_t normal_compress_rate:4; /*0.5 as the unit*/
};

struct rtsjpgenc_encin {
	uint32_t src_busLuma;
	uint32_t src_busChroma;
	uint32_t out_bus_buf;
	uint32_t out_buf_size;
	void *p_outbuf;
	uint32_t out_bytesused;
};

int rtsjpgenc_init(RtsJpgEncInst *pinst);
int rtsjpgenc_release(RtsJpgEncInst inst);
int rtsjpgenc_set_config(RtsJpgEncInst inst, struct rtsjpgenc_config *pcfg);
int rtsjpgenc_encode(RtsJpgEncInst inst, struct rtsjpgenc_encin *pencin);
int rtsjpgenc_get_coding_ctrl(RtsJpgEncInst inst,
			      struct rtsjpgenc_coding_ctrl *ctrl);
int rtsjpgenc_set_coding_ctrl(RtsJpgEncInst inst,
			      struct rtsjpgenc_coding_ctrl *ctrl);

int rtsjpgenc_set_epoll_hook(RtsJpgEncInst inst, void *master,
			     int (*hook_func)(void *master, int fd));
int rtsjpgenc_check_done(RtsJpgEncInst inst);
int rtsjpgenc_make_rdy(RtsJpgEncInst inst);
int rtsjpgenc_use_sigio(RtsJpgEncInst inst, int sigio_need);
#ifdef __cplusplus
}
#endif
#endif
