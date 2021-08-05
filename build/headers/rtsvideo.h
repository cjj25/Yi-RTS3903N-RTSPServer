/*
 * Realtek Semiconductor Corp.
 *
 * include/rtsvideo.h
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _INCLUDE_RTSVIDEO_H
#define _INCLUDE_RTSVIDEO_H
#include <stdint.h>
#include <rtsavdef.h>

#ifdef __cplusplus
extern "C"
{
#endif

enum enum_rts_video_ctrl_id {
	RTS_VIDEO_CTRL_ID_BRIGHTNESS = 1,
	RTS_VIDEO_CTRL_ID_CONTRAST,
	RTS_VIDEO_CTRL_ID_HUE,
	RTS_VIDEO_CTRL_ID_SATURATION,
	RTS_VIDEO_CTRL_ID_SHARPNESS,
	RTS_VIDEO_CTRL_ID_GAMMA,
	RTS_VIDEO_CTRL_ID_AWB_CTRL,
	RTS_VIDEO_CTRL_ID_WB_TEMPERATURE,
	RTS_VIDEO_CTRL_ID_BLC,
	RTS_VIDEO_CTRL_ID_GAIN,
	RTS_VIDEO_CTRL_ID_PWR_FREQUENCY,
	RTS_VIDEO_CTRL_ID_EXPOSURE_MODE,
	RTS_VIDEO_CTRL_ID_EXPOSURE_PRIORITY,
	RTS_VIDEO_CTRL_ID_EXPOSURE_TIME,
	RTS_VIDEO_CTRL_ID_AF,
	RTS_VIDEO_CTRL_ID_FOCUS,
	RTS_VIDEO_CTRL_ID_ZOOM,
	RTS_VIDEO_CTRL_ID_PAN,
	RTS_VIDEO_CTRL_ID_TILT,
	RTS_VIDEO_CTRL_ID_ROLL,
	RTS_VIDEO_CTRL_ID_FLIP,
	RTS_VIDEO_CTRL_ID_MIRROR,
	RTS_VIDEO_CTRL_ID_ROTATE,
	RTS_VIDEO_CTRL_ID_ISP_SPECIAL_EFFECT,
	RTS_VIDEO_CTRL_ID_EV_COMPENSATE,
	RTS_VIDEO_CTRL_ID_COLOR_TEMPERATURE_ESTIMATION,
	RTS_VIDEO_CTRL_ID_AE_LOCK,
	RTS_VIDEO_CTRL_ID_AWB_LOCK,
	RTS_VIDEO_CTRL_ID_AF_LOCK,
	RTS_VIDEO_CTRL_ID_LED_TOUCH_MODE,
	RTS_VIDEO_CTRL_ID_LED_FLASH_MODE,
	RTS_VIDEO_CTRL_ID_ISO,
	RTS_VIDEO_CTRL_ID_SCENE_MODE,
	RTS_VIDEO_CTRL_ID_ROI_MODE,
	RTS_VIDEO_CTRL_ID_3A_STATUS,
	RTS_VIDEO_CTRL_ID_IDEA_EYE_SENSITIVITY,
	RTS_VIDEO_CTRL_ID_IDEA_EYE_STATUS,
	RTS_VIDEO_CTRL_ID_IEDA_EYE_MODE,
	RTS_VIDEO_CTRL_ID_GRAY_MODE,
	RTS_VIDEO_CTRL_ID_WDR_MODE,
	RTS_VIDEO_CTRL_ID_WDR_LEVEL,
	RTS_VIDEO_CTRL_ID_GREEN_BALANCE,
	RTS_VIDEO_CTRL_ID_RED_BALANCE,
	RTS_VIDEO_CTRL_ID_BLUE_BALANCE,
	RTS_VIDEO_CTRL_ID_AE_GAIN,
	RTS_VIDEO_CTRL_ID_3DNR,
	RTS_VIDEO_CTRL_ID_DEHAZE,
	RTS_VIDEO_CTRL_ID_IR_MODE,
	RTS_VIDEO_CTRL_ID_SMART_IR_MODE,
	RTS_VIDEO_CTRL_ID_SMART_IR_MANUAL_LEVEL,
	RTS_VIDEO_CTRL_ID_IN_OUT_DOOR_MODE,
	RTS_VIDEO_CTRL_ID_NOISE_REDUCTION,
	RTS_VIDEO_CTRL_ID_DETAIL_ENHANCEMENT,
	RTS_VIDEO_CTRL_ID_LDC,
	RTS_VIDEO_CTRL_ID_RESERVED
};

enum {
	RTS_ISP_AE_AUTO = 0,
	RTS_ISP_AE_MANUAL = 1
};

enum {
	RTS_ISP_AE_PRIORITY_MANUAL = 0,
	RTS_ISP_AE_PRIORITY_AUTO = 1
};

enum {
	RTS_ISP_AWB_TEMPERATURE = 0,
	RTS_ISP_AWB_AUTO = 1,
	RTS_ISP_AWB_COMPONENT
};

enum RTS_ISP_WDR_MODE {
	RTS_ISP_WDR_DISABLE = 0,
	RTS_ISP_WDR_MANUAL,
	RTS_ISP_WDR_AUTO,
	RTS_ISP_WDR_RESERVED,
};

enum RTS_ISP_IR_MODE {
	RTS_ISP_IR_DAY = 0,
	RTS_ISP_IR_NIGHT = 1,
	RTS_ISP_IR_WHITE_LIGHT = 2
};

enum RTS_ISP_SMART_IR_MODE {
	RTS_ISP_SMART_IR_MODE_DISABLE = 0,
	RTS_ISP_SMART_IR_MODE_AUTO = 1,
	RTS_ISP_SMART_IR_MODE_HIGH_LIGHT_PRIORITY = 2,
	RTS_ISP_SMART_IR_MODE_LOW_LIGHT_PRIORITY = 3,
	RTS_ISP_SMART_IR_MODE_MANUAL = 4
};

enum RTS_ISP_IN_OUT_DOOR_MODE {
	RTS_ISP_DOOR_MODE_OUT = 0,
	RTS_ISP_DOOR_MODE_IN = 1,
	RTS_ISP_DOOR_MODE_AUTO = 2
};

struct rts_video_control {
	uint32_t type;
	char name[32];
	int32_t minimum;
	int32_t maximum;
	int32_t step;
	int32_t default_value;
	int32_t current_value;
	uint32_t flags;
	uint32_t reserved[4];
};


enum {
	RTS_AV_BLK_TYPE_UNDEFINED = 0,
	RTS_AV_BLK_TYPE_RECT,
	RTS_AV_BLK_TYPE_GRID,
};

struct rts_video_coordinate {
	int32_t x;
	int32_t y;
};

struct rts_video_size {
	uint32_t width;
	uint32_t height;
};

struct rts_video_rect {
	union {
		struct {
			struct rts_video_coordinate start;
			struct rts_video_coordinate end;
		};
		struct {
			int32_t left;
			int32_t top;
			int32_t right;
			int32_t bottom;
		};
	};
};

struct rts_video_grid_cell {
	uint32_t width;
	uint32_t height;
};

struct rts_video_grid_size {
	uint32_t rows;
	uint32_t columns;
};

struct rts_video_grid_bitmap {
	uint8_t *vm_addr;
	uint32_t length;
	uint32_t reserved[4];
};

struct rts_video_grid {
	struct rts_video_coordinate start;
	struct rts_video_grid_cell cell;
	struct rts_video_grid_size size;

	struct rts_video_grid_bitmap bitmap;

	uint32_t reserved[4];
};

enum {
	RTS_VIDEO_MD_DATA_TYPE_AVGY   = (1 << 0),
	RTS_VIDEO_MD_DATA_TYPE_RLTPRE = (1 << 1),
	RTS_VIDEO_MD_DATA_TYPE_RLTCUR = (1 << 2),
	RTS_VIDEO_MD_DATA_TYPE_BACKY  = (1 << 3),
	RTS_VIDEO_MD_DATA_TYPE_BACKF  = (1 << 4),
	RTS_VIDEO_MD_DATA_TYPE_BACKC  = (1 << 5)
};

enum {
	RTS_VIDEO_MD_DETECT_USER_TRIG = 0,
	RTS_VIDEO_MD_DETECT_HW
};

struct rts_video_md_data {
	uint8_t bpp;
	void *vm_addr;
	uint32_t length;
	uint32_t reserved[4];
};

struct rts_video_md_type_data {
	uint32_t type;
	union {
		struct rts_video_md_data *data;
	};
	uint32_t reserved[4];
};

struct rts_video_md_result {
	unsigned int count;
	struct rts_video_md_type_data *results;

	uint32_t reserved[4];
};


struct rts_video_md_ops {
	int (*motion_detected)(int idx, void *priv);
	int (*motion_received)(int idx, struct rts_video_md_result *result,
			       void *priv);
	void *priv;

	uint32_t reserved[4];
};

struct rts_video_md_block {
	const int idx;
	const int type;
	const uint32_t supported_data_mode;
	const uint32_t supported_detect_mode;
	const uint32_t supported_grid_num;

	int enable;
	struct rts_video_grid area;

	uint32_t data_mode_mask;
	uint32_t detect_mode;

	struct rts_video_size res_size;

	uint32_t sensitivity;
	uint32_t percentage;
	uint32_t frame_interval;

	struct rts_video_md_ops ops;

	uint32_t reserved[4];
};

struct rts_video_md_attr {
	const int number;
	struct rts_video_md_block *blocks;

	uint32_t reserved[4];
};


struct rts_video_mask_block {
	const int type;
	const uint32_t supported_grid_num;
	int enable;
	union {
		struct rts_video_grid area;
		struct rts_video_rect rect;
	};
	struct rts_video_size res_size;

	uint32_t reserved[4];
};

struct rts_video_mask_attr {
	uint32_t color;    /*rgb24*/
	const int number;
	struct rts_video_mask_block *blocks;

	uint32_t reserved[4];
};

enum {
	OSD_TIME_FMT_NO = 0,	/*not show time*/
	OSD_TIME_FMT_24,
	OSD_TIME_FMT_12,
	OSD_TIME_FMT_12_1,
	OSD_TIME_FMT_12_2,
	OSD_TIME_FMT_12_3,
	OSD_TIME_FMT_12_4,
	OSD_TIME_FMT_12_5,
	OSD_TIME_FMT_12_6,
	OSD_TIME_FMT_12_7,
	OSD_TIME_FMT_RESERVED
};

enum {
	OSD_DATE_FMT_NO = 0,	/*not show date*/
	OSD_DATE_FMT_0,		/*dd/MM/yyyy, eg. 26/05/2015*/
	OSD_DATE_FMT_1,		/*dd/MM/yy, eg. 26/05/15*/
	OSD_DATE_FMT_2,		/*d/M/yy, eg. 26/5/15*/
	OSD_DATE_FMT_3,		/*M/d/yyyy, eg. 5/26/2015*/
	OSD_DATE_FMT_4,		/*M/d/yy, eg. 5/26/15*/
	OSD_DATE_FMT_5,		/*MM/dd/yy, eg. 05/26/15*/
	OSD_DATE_FMT_6,		/*MM/dd/yyyy, eg. 05/26/2015*/
	OSD_DATE_FMT_7,		/*yyyy/M/d, eg. 2015/5/26*/
	OSD_DATE_FMT_8,		/*yyyy-M-d, eg. 2015-5-26*/
	OSD_DATE_FMT_9,		/*yyyy-MM-dd, eg. 2015-05-26*/
	OSD_DATE_FMT_10,	/*yyyy/MM/dd, eg. 2015/05/26*/
	OSD_DATE_FMT_11,	/*yy-MM-dd, eg. 15-05-26*/
	OSD_DATE_FMT_12,	/*yy/M/d, eg. 15/5/26*/
	OSD_DATE_FMT_13,	/*yy-M-d, eg. 15-5-26*/
	OSD_DATE_FMT_14,	/*yy/MM/dd, eg. 15/05/26*/
	OSD_DATE_FMT_15,	/*yyyy.mm.dd, eg. 2015.05.26*/
	OSD_DATE_FMT_16,	/*dd.mm.yyyy, eg. 26.05.2015*/
	OSD_DATE_FMT_17,	/*mm.dd.yyyy, eg. 05.26.2015*/
	OSD_DATE_FMT_18,	/*mm-dd-yyyy, eg. 05-26-2015*/
	OSD_DATE_FMT_19,	/*dd-mm-yyyy, eg. 26-05-2015*/
	OSD_DATE_FMT_RESERVED
};

struct rts_video_osd_image {
	enum rts_pix_fmt_e pixel_fmt;
	uint32_t width;
	uint32_t height;
	void *data;
};

struct rts_video_osd_block {
	struct rts_video_rect rect;
	uint8_t bg_enable;
	uint32_t bg_color;
	uint32_t ch_color;

	uint8_t h_gap : 4,
		v_gap : 4;

	uint8_t flick_enable;
	uint32_t flick_speed;
	uint8_t char_color_alpha;

	uint8_t stroke_enable;
	uint8_t stroke_direct;
	uint8_t stroke_delta;

	char *pshowtext;
	struct rts_video_osd_image *pimg;

	uint32_t reserved[4];
};

struct rts_video_osd_attr {
	const int number;
	struct rts_video_osd_block *blocks;

	unsigned int time_fmt;
	uint8_t time_blkidx;
	int time_pos;
	unsigned int date_fmt;
	uint8_t date_blkidx;
	int date_pos;

	char *single_lib_name;
	char *double_lib_name;

	uint8_t osd_char_w;
	uint8_t osd_char_h;

	int rotation;

	uint32_t reserved[4];
};

enum rts_osd2_blk_fmt {
	RTS_OSD2_BLK_FMT_1BPP = RTS_PIX_FMT_1BPP,
	RTS_OSD2_BLK_FMT_RGBA1111 = RTS_PIX_FMT_RGBA1111,
	RTS_OSD2_BLK_FMT_RGBA2222 = RTS_PIX_FMT_RGBA2222,
	RTS_OSD2_BLK_FMT_RGBA5551 = RTS_PIX_FMT_RGBA5551,
	RTS_OSD2_BLK_FMT_RGBA4444 = RTS_PIX_FMT_RGBA4444,
	RTS_OSD2_BLK_FMT_RGBA8888 = RTS_PIX_FMT_RGBA8888
};

struct rts_video_osd2_block {
	struct rts_video_rect rect;

	struct {
		enum rts_osd2_blk_fmt pixel_fmt;
		void *pdata;
		uint32_t length;
		uint32_t pure_color;
	} picture;

	struct {
		int flick_enable;
		uint32_t show_time;
		uint32_t hide_time;
	} flick;

	uint8_t enable;
	uint32_t fixed_buf_len;
	uint32_t reserved[4];
};

struct rts_video_osd2_attr {
	const int number;
	struct rts_video_osd2_block *blocks;

	uint32_t reserved[4];
};

enum rts_bitrate_mode {
	RTS_BITRATE_MODE_CBR        = (1 << 1),
	RTS_BITRATE_MODE_VBR        = (1 << 2),
	RTS_BITRATE_MODE_C_VBR      = (1 << 3),
	RTS_BITRATE_MODE_S_VBR      = (1 << 4),
};

enum rts_gop_mode {
	RTS_GOP_MODE_NORMAL         = (1 << 1),
	RTS_GOP_MODE_SP             = (1 << 2),
};

struct rts_video_h264_info {
	int sps_pps_len;
	char sps_pps[64];

	uint32_t reserved[4];
};

struct rts_video_h264_ctrl {
	const uint32_t supported_bitrate_mode;
	const uint32_t supported_gop_mode;
	uint32_t bitrate_mode;
	uint32_t gop_mode;

	uint32_t bitrate;
	uint32_t max_bitrate;
	uint32_t min_bitrate;

	int32_t qp;
	uint32_t max_qp;
	uint32_t min_qp;
	int32_t intra_qp_delta;

	uint32_t gop;

	uint32_t slice_size;
	uint32_t sei_messages;
	uint32_t video_full_range;
	uint32_t constrained_intra_prediction;
	uint32_t disable_deblocking_filter;
	uint32_t enable_cabac;
	uint32_t cabac_init_idc;
	uint32_t transform8x8mode;
	uint32_t gdr;

	uint32_t hrd;
	uint32_t hrd_cpb_size;
	int32_t longterm_pic_rate;

	uint32_t br_level;
	uint32_t super_p_period;
	int mbrc_en;
	float mbrc_qp_gain;
	int32_t mbrc_qp_delta_range;

	uint32_t reserved[4];
};

struct rts_video_mjpeg_ctrl {
	uint16_t normal_compress_rate:4; /*0.5 as the unit*/

	const uint16_t ncr_max;
	const uint16_t ncr_min;
	const uint16_t ncr_step;

	uint32_t reserved[4];
};

enum rts_video_roi_type {
	RTS_VIDEO_ROI_UNKNOWN = 0,
	RTS_VIDEO_ROI_H264,
	RTS_VIDEO_ROI_RESERVED
};

struct rts_video_roi_ctrl {
	const int index;
	int enable;
	struct rts_video_rect area;
	int32_t value;

	const int32_t min;
	const int32_t max;
	const int32_t step;

	uint32_t reserved[4];
};

struct rts_video_roi_attr {
	const int type;

	struct rts_video_roi_ctrl *roi;
	const int count;

	uint32_t reserved[4];
};

struct rts_isp_ae_ctrl {
	const struct rts_video_size window_size;
	const uint32_t window_num;
	const uint32_t histogram_num;

	int mode;

	struct {
		uint16_t total_gain;
		struct {
			uint16_t analog;
			uint16_t digital;
			uint16_t isp_digital;
		} gain;
		uint32_t exposure_time;

		uint32_t reserved[4];
	} _manual;

	struct {
		uint8_t * const win_weights;

		int target_delta;
		uint16_t gain_max;
		uint8_t min_fps;

		uint32_t reserved[4];
	} _auto;

	const struct {
		uint8_t y_mean;
		uint8_t *win_y_means;
		uint16_t *histogram_info;

		uint32_t reserved[4];
	} statis;

	uint32_t reserved[4];
};

struct rts_isp_awb_gain {
	uint16_t r_gain;
	uint16_t b_gain;
};

struct rts_isp_awb_ctrl {
	const struct rts_video_size window_size;
	const uint32_t window_num;

	int mode;

	struct {
		struct rts_isp_awb_gain adjustment;

		uint32_t reserved[4];
	} _auto;

	struct {
		uint32_t temperature;

		uint32_t reserved[4];
	} _manual;

	struct {
		uint16_t red;
		uint16_t green;
		uint16_t blue;

		uint32_t reserved[4];
	} _component;

	const struct {
		uint8_t *r_means;
		uint8_t *g_means;
		uint8_t *b_means;

		uint32_t reserved[4];
	} statis;

	uint32_t reserved[4];
};

enum {
	RTS_ISP_CT_2800K = 0, /*A*/
	RTS_ISP_CT_3000K, /*U30*/
	RTS_ISP_CT_4000K, /*CWF*/
	RTS_ISP_CT_5000K, /*D50*/
	RTS_ISP_CT_6500K, /*D65*/
	RTS_ISP_CT_7500K, /*D75*/
	RTS_ISP_CT_RESERVED
};

struct rts_isp_af_ctrl {
	const struct rts_video_size window_size;
	const uint32_t window_num;

	const struct {
		uint32_t whole_win_sum;
		uint32_t center_win_sum;
		uint32_t *win_sum;

		uint32_t reserved[4];
	} statis;

	uint32_t reserved[4];
};

struct rts_av_h1_roi_map {
	const uint32_t x_mbs;
	const uint32_t y_mbs;
	const uint8_t mb_width;
	const uint8_t mb_height;

	int roi_map_enable;
	uint8_t *map;

	const int qp_offset_num;
	int qp_offset[3];

	uint32_t reserved[4];
};

struct rts_isp_snr_crop {
	struct rts_video_coordinate minimum;
	struct rts_video_coordinate maximum;
	struct rts_video_coordinate step;
	struct rts_video_coordinate default_value;
	struct rts_video_coordinate current_value;
};

/*!
 * set bitmap for motion detect or private mask,
 *
 * @return 0 : success, minus : fail
 */
int rts_set_isp_bitmap(uint8_t *bitmap, int length, int index);

/*!
 * clear bitmap for motion detect or private mask,
 *
 * @return 0 : success, minus : fail
 */
int rts_clear_isp_bitmap(uint8_t *bitmap, int length, int index);

/*!
 * get bitmap for motion detect or private mask,
 *
 * @return 1 : set, 0 : clear, minus : fail
 */
int rts_get_isp_bitmap(uint8_t *bitmap, int length, int index);

/*!
 * set all bitmap for motion detect or private mask,
 *
 * @return 0 : success, minus : fail
 */
int rts_set_all_isp_bitmap(uint8_t *bitmap, int length);

/*!
 * clear all bitmap for motion detect or private,
 *
 * @return 0 : success, minus : fail
 */
int rts_clear_all_isp_bitmap(uint8_t *bitmap, int length);

int rts_av_get_isp_ctrl(uint32_t id, struct rts_video_control *pctrl);
int rts_av_set_isp_ctrl(uint32_t id, struct rts_video_control *pctrl);

int rts_av_query_isp_md(struct rts_video_md_attr **attr,
			uint32_t res_width, uint32_t res_height);
void rts_av_release_isp_md(struct rts_video_md_attr *attr);
int rts_av_set_isp_md(struct rts_video_md_attr *attr);
int rts_av_get_isp_md(struct rts_video_md_attr *attr);
int rts_av_trig_isp_md(struct rts_video_md_attr *attr, int mdidx);
int rts_av_check_isp_md_status(struct rts_video_md_attr *attr, int mdidx);
int rts_av_init_md_result(struct rts_video_md_result *result,
			  uint32_t data_mode_mask);
void rts_av_uninit_md_result(struct rts_video_md_result *result);
int rts_av_get_isp_md_result(struct rts_video_md_attr *attr, int mdidx,
			     struct rts_video_md_result *result);

int rts_av_query_isp_mask(struct rts_video_mask_attr **attr,
			  uint32_t res_width, uint32_t res_height);
int rts_av_set_isp_mask(struct rts_video_mask_attr *attr);
int rts_av_get_isp_mask(struct rts_video_mask_attr *attr);
void rts_av_release_isp_mask(struct rts_video_mask_attr *attr);

int rts_av_query_isp_osd(unsigned int chnno, struct rts_video_osd_attr **attr);
int rts_av_set_isp_osd(struct rts_video_osd_attr *attr);
int rts_av_get_isp_osd(struct rts_video_osd_attr *attr);
int rts_av_refresh_isp_osd_datetime(struct rts_video_osd_attr *attr);
void rts_av_release_isp_osd(struct rts_video_osd_attr *attr);

int rts_av_query_osd2(unsigned int chnno, struct rts_video_osd2_attr **attr);
int rts_av_set_osd2_single(struct rts_video_osd2_attr *attr, int blkidx);
int rts_av_get_osd2_single(struct rts_video_osd2_attr *attr, int blkidx);
int rts_av_set_osd2(struct rts_video_osd2_attr *attr);
int rts_av_get_osd2(struct rts_video_osd2_attr *attr);
int rts_av_resume_osd2_single(struct rts_video_osd2_attr *attr, int blkidx);
int rts_av_pause_osd2_single(struct rts_video_osd2_attr *attr, int blkidx);
int rts_av_set_osd2_color_table(struct rts_video_osd2_attr *attr,
			int fmt, uint32_t val,
			uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t rts_av_get_osd2_color_table(struct rts_video_osd2_attr *attr,
			int fmt, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void rts_av_release_osd2(struct rts_video_osd2_attr *attr);

int rts_av_get_h264_mediainfo(unsigned int chnno,
			      struct rts_video_h264_info *info);
int rts_av_get_h264_profile(unsigned int chnno, int *profile);
int rts_av_query_h264_ctrl(unsigned int chnno,
			   struct rts_video_h264_ctrl **ppctrl);
void rts_av_release_h264_ctrl(struct rts_video_h264_ctrl *ctrl);
int rts_av_set_h264_ctrl(struct rts_video_h264_ctrl *ctrl);
int rts_av_get_h264_ctrl(struct rts_video_h264_ctrl *ctrl);
int rts_av_request_h264_key_frame(unsigned int chnno);
int rts_av_set_h264_color_conversion(unsigned int chnno, int color_type,
				     struct rts_color_coef_t *coef);

int rts_av_query_h264_roi(unsigned int chnno, struct rts_video_roi_attr **attr);
void rts_av_release_h264_roi(struct rts_video_roi_attr *attr);
int rts_av_set_h264_roi(struct rts_video_roi_attr *attr);
int rts_av_get_h264_roi(struct rts_video_roi_attr *attr);
int rts_av_get_h264_crop(int chnno, struct rts_video_rect *rect);
int rts_av_set_h264_crop(int chnno, struct rts_video_rect *rect);

int rts_av_query_mjpeg_ctrl(unsigned int chnno,
			    struct rts_video_mjpeg_ctrl **ppctrl);
void rts_av_release_mjpeg_ctrl(struct rts_video_mjpeg_ctrl *ctrl);
int rts_av_get_mjpeg_ctrl(struct rts_video_mjpeg_ctrl *ctrl);
int rts_av_set_mjpeg_ctrl(struct rts_video_mjpeg_ctrl *ctrl);

int rts_av_query_isp_ae(struct rts_isp_ae_ctrl **ae);
void rts_av_release_isp_ae(struct rts_isp_ae_ctrl *ae);
int rts_av_get_isp_ae(struct rts_isp_ae_ctrl *ae);
int rts_av_set_isp_ae(struct rts_isp_ae_ctrl *ae);
int rts_av_refresh_isp_ae_statis(struct rts_isp_ae_ctrl *ae);

int rts_av_query_isp_awb(struct rts_isp_awb_ctrl **awb);
void rts_av_release_isp_awb(struct rts_isp_awb_ctrl *awb);
int rts_av_get_isp_awb(struct rts_isp_awb_ctrl *awb);
int rts_av_set_isp_awb(struct rts_isp_awb_ctrl *awb);
int rts_av_refresh_isp_awb_statis(struct rts_isp_awb_ctrl *awb);
int rts_av_get_isp_awb_ct_gain(uint8_t ct, struct rts_isp_awb_gain *gain);

int rts_av_query_isp_af(struct rts_isp_af_ctrl **af);
void rts_av_release_isp_af(struct rts_isp_af_ctrl *af);
int rts_av_get_isp_af(struct rts_isp_af_ctrl *af);
int rts_av_set_isp_af(struct rts_isp_af_ctrl *af);
int rts_av_refresh_isp_af_statis(struct rts_isp_af_ctrl *af);

int rts_av_get_isp_fov_mode(unsigned int chnno, int *val);
int rts_av_set_isp_fov_mode(unsigned int chnno, int val);

int rts_av_query_isp_ability(unsigned int chnno,
			     struct rts_isp_ability **isp_ability);
void rts_av_release_isp_ability(struct rts_isp_ability *isp_ability);
int rts_av_set_isp_dynamic_fps(uint8_t fps);
int rts_av_get_isp_dynamic_fps(void);

int rts_av_query_h264_roi_map(int chnno, struct rts_av_h1_roi_map **ppmap);
int rts_av_set_h264_roi_map(struct rts_av_h1_roi_map *pmap);
void rts_av_release_h264_roi_map(struct rts_av_h1_roi_map *pmap);

int rts_av_get_isp_snr_crop(struct rts_isp_snr_crop *crop);
int rts_av_set_isp_snr_crop(struct rts_isp_snr_crop *crop);
int rts_av_cvrt_point_res(struct rts_point_res *src,
	struct rts_point_res *dst, struct rts_point_con *constraint);
char *rts_av_get_supported_snr_name(void);
int rts_av_get_isp_daynight_statis(void);

#ifdef __cplusplus
}
#endif
#endif
