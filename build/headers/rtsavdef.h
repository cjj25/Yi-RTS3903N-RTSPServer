/*
 * Realtek Semiconductor Corp.
 *
 * inc/rtsavdef.h
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _INC_RTSAVDEF_H
#define _INC_RTSAVDEF_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <rtscolor.h>
#include <rtsdef.h>

#define rts_av_fourcc(a, b, c, d)\
	((uint32_t)(a) | ((uint32_t)(b) << 8) | \
	 ((uint32_t)(c)<<16) | ((uint32_t)((d) & 0x7f)<<24))

#define RTS_AV_FMT_AUDIO		0x8000
enum RTS_AV_FMT {
	RTS_AV_FMT_UNDEFINED = 0x0,
	RTS_V_FMT_YUYV = RTS_PIX_FMT_YUYV,
	RTS_V_FMT_YUV420PLANAR = RTS_PIX_FMT_YUV420M,
	RTS_V_FMT_YUV420SEMIPLANAR = RTS_PIX_FMT_NV12,	//V4L2_PIX_FMT_NV12
	RTS_V_FMT_YUV422SEMIPLANAR = RTS_PIX_FMT_NV16,
	RTS_V_FMT_MJPEG = RTS_PIX_FMT_MJPEG,
	RTS_V_FMT_H264 = RTS_PIX_FMT_H264,

	RTS_A_FMT_AUDIO = RTS_AV_FMT_AUDIO | 0x1,
	RTS_A_FMT_MP3,
	RTS_A_FMT_ULAW,
	RTS_A_FMT_ALAW,
	RTS_A_FMT_G726,
	RTS_A_FMT_AMRNB,
	RTS_A_FMT_AAC,
	RTS_A_FMT_SBC,
	RTS_A_FMT_OPUS,
};

/*deprecated*/
enum {
	rts_av_fmt_undefined = RTS_AV_FMT_UNDEFINED,
	rts_v_fmt_yuyv = RTS_V_FMT_YUYV,
	rts_v_fmt_yuv420planar = RTS_V_FMT_YUV420PLANAR,
	rts_v_fmt_yuv420semiplanar = RTS_V_FMT_YUV420SEMIPLANAR,
	rts_v_fmt_yuv422semiplanar = RTS_V_FMT_YUV422SEMIPLANAR,
	rts_v_fmt_mjpeg = RTS_V_FMT_MJPEG,
	rts_v_fmt_h264 = RTS_V_FMT_H264,

	rts_a_fmt_audio = RTS_A_FMT_AUDIO,
} __attribute__ ((deprecated));

enum rts_av_rotation {
	RTS_AV_ROTATION_0 = 0,
	RTS_AV_ROTATION_90R = 1,
	RTS_AV_ROTATION_90L = 2,
	RTS_AV_ROTATION_180 = 3,
};

/*deprecated*/
enum {
	rts_av_rotation_0 = RTS_AV_ROTATION_0,
	rts_av_rotation_90r = RTS_AV_ROTATION_90R,
	rts_av_rotation_90l = RTS_AV_ROTATION_90L,
	rts_av_rotation_180 = RTS_AV_ROTATION_180
} __attribute__ ((deprecated));

enum rts_av_ability_type {
	RTS_AV_ABILITY_UNDEFINED = 0,
	RTS_AV_ABILITY_V4L2,
	RTS_AV_ABILITY_ISP,
	RTS_AV_ABILITY_AUDIO,
	RTS_AV_ABILITY_RESERVED,
};

enum rts_v4l2_frmsizetypes {
	RTS_V4L2_FRMSIZE_TYPE_DISCRETE = 1,
	RTS_V4L2_FRMSIZE_TYPE_CONTINUOUS = 2,
	RTS_V4L2_FRMSIZE_TYPE_STEPWISE = 3
};

enum rts_v4l2_frmivaltypes {
	RTS_V4L2_FRMIVAL_TYPE_DISCRETE = 1,
	RTS_V4L2_FRMIVAL_TYPE_CONTINUOUS = 2,
	RTS_V4L2_FRMIVAL_TYPE_STEPWISE = 3
};

struct rts_fract {
	uint32_t numerator;
	uint32_t denominator;
};

struct rts_v4l2_frmival_stepwise {
	struct rts_fract min;
	struct rts_fract max;
	struct rts_fract step;
};

struct rts_v4l2_resolution_discrets {
	uint32_t width;
	uint32_t height;
};

struct rts_v4l2_resolution_stepwise {
	uint32_t min_width;
	uint32_t max_width;
	uint32_t step_width;
	uint32_t min_height;
	uint32_t max_height;
	uint32_t step_height;
};

struct rts_v4l2_frmival {
	uint32_t type;
	union {
		struct rts_fract                 discrete;
		struct rts_v4l2_frmival_stepwise stepwise;
	};
};

struct rts_v4l2_resolution {
	uint32_t type;
	union {
		struct rts_v4l2_resolution_discrets discrete;
		struct rts_v4l2_resolution_stepwise stepwise;
	};
	int number;
	struct rts_v4l2_frmival *pfrmivals;
};

struct rts_v4l2_format {
	uint32_t format;
	int number;
	struct rts_v4l2_resolution *presolutions;
};

struct rts_v4l2_ability {
	int number;
	struct rts_v4l2_format *pformats;
};

struct rts_isp_ability {
	int fmt_number;
	enum RTS_AV_FMT *pformats;
	struct rts_v4l2_resolution_stepwise resolution;
	int frmival_num;
	struct rts_fract *pfrmivals;
};

struct rts_audio_param {
	uint32_t format;
	uint32_t channels;
	uint32_t rate;
};

struct rts_audio_ability_t {
	int number;
	struct rts_audio_param *ability;
};

struct rts_av_ability_t {
	const uint32_t type;
	union {
		struct rts_v4l2_ability v4l2_ability;
		struct rts_isp_ability isp_ability;
		struct rts_audio_ability_t audio_ability;
	};
};

/*!
 * convert v4l2 pixelformat to rts_av_fmt
 */
enum RTS_AV_FMT rts_get_av_fmt_from_v4l2_fmt(uint32_t pixelformat);

/*!
 * convert rts_av_fmt to v4l2 pixelformat
 */
uint32_t rts_get_v4l2_fmt_from_av_fmt(enum RTS_AV_FMT fmt);

enum {
	RTSTREAM_PKT_FLAG_KEY			= (1 << 0),
	RTSTREAM_PKT_FLAG_NO_OUTPUT		= (1 << 1),
	RTSTREAM_PKT_FLAG_MEM_FROM_DEVICE	= (1 << 2),
	RTSTREAM_PKT_FLAG_MEM_TO_DEVICE		= (1 << 3),
	RTSTREAM_PKT_FLAG_SP                    = (1 << 4), /*super p flag*/
};

struct rts_av_buffer {
	void *vm_addr;
	uint32_t length;
	uint32_t bytesused;
	uint32_t phy_addr;
	uint32_t flags;
	uint32_t index;
	uint32_t type;
	uint32_t volume_l;
	uint32_t volume_r;
	uint64_t timestamp;
	void *priv;
};

struct rts_av_profile {
	enum RTS_AV_FMT fmt;
	union {
		struct {
			uint32_t width;
			uint32_t height;
			uint32_t numerator;
			uint32_t denominator;
		} video;
		struct {
			uint32_t samplerate;
			uint32_t bitfmt;
			uint32_t channels;
			uint32_t reserved;
		} audio;
	};
};

#define RTS_AV_ID_ISP			rts_av_fourcc('i', 's', 'p', 0)
#define RTS_AV_ID_H264			rts_av_fourcc('h', '2', '6', '4')
#define RTS_AV_ID_MJPGENC		rts_av_fourcc('m', 'j', 'p', 'g')
#define RTS_AV_ID_OSD			rts_av_fourcc('o', 's', 'd', 0)
#define RTS_AV_ID_OSDENC		rts_av_fourcc('o', 's', 'd', '2')
#define RTS_AV_ID_AUDIO_PLAYBACK	rts_av_fourcc('a', 'u', 'p', 'l')
#define RTS_AV_ID_AUDIO_CAPTURE		rts_av_fourcc('a', 'u', 'c', 'a')
#define RTS_AV_ID_AUDIO_ENCODE		rts_av_fourcc('a', 'e', 'n', 'c')
#define RTS_AV_ID_AUDIO_DECODE		rts_av_fourcc('a', 'd', 'e', 'c')
#define RTS_AV_ID_AUDIO_RESAMPLE	rts_av_fourcc('a', 'r', 's', 'm')
#define RTS_AV_ID_AUDIO_AEC		rts_av_fourcc('a', 'e', 'c', 0)
#define RTS_AV_ID_AUDIO_AMIXER		rts_av_fourcc('a', 'm', 'i', 'x')

struct rts_isp_attr {
	int isp_buf_num;
	int isp_id;	/*it will only be used in get attr*/
};

enum rts_h264_profile {
	H264_PROFILE_UNKNOWN,
	H264_PROFILE_BASE,
	H264_PROFILE_MAIN,
	H264_PROFILE_HIGH
};

enum rts_h264_level {
	H264_LEVEL_UNKNOWN = 0,
	H264_LEVEL_1,
	H264_LEVEL_1_b,
	H264_LEVEL_1_1,
	H264_LEVEL_1_2,
	H264_LEVEL_1_3,
	H264_LEVEL_2,
	H264_LEVEL_2_1,
	H264_LEVEL_2_2,
	H264_LEVEL_3,
	H264_LEVEL_3_1,
	H264_LEVEL_3_2,
	H264_LEVEL_4,
	H264_LEVEL_4_1,
	H264_LEVEL_4_2,
	H264_LEVEL_5,
	H264_LEVEL_5_1,
	H264_LEVEL_RESERVED
};

struct rts_h264_attr {
	enum rts_h264_level level;

	int qp;
	unsigned int bps;
	unsigned int gop;
	enum rts_av_rotation rotation;
	int videostab;
};

struct rts_jpgenc_attr {
	enum rts_av_rotation rotation;
};

struct rts_audio_attr {
	char dev_node[64];
	uint32_t format;
	uint32_t channels;
	uint32_t rate;

	unsigned long period_frames;
};

enum {
	RTS_AUDIO_AMIXER_DECODE_MIXER = 0,
	RTS_AUDIO_AMIXER_DECODE = 1,
};

struct rts_audio_encode_attr {
	int codec_id;
	uint32_t bitrate;
};

enum {
	RTS_AV_CB_TYPE_ASYNC = 0,
	RTS_AV_CB_TYPE_SYNC,
};

typedef void (*rts_av_cb_func)(void *priv, struct rts_av_profile *profile,
			       struct rts_av_buffer *buffer);

struct rts_av_callback {
	rts_av_cb_func func;
	void *priv;
	unsigned int start;
	int times;
	unsigned int interval;
	int type;
};

enum {
	RTS_AV_FLAG_DROPPABLE = (0x1 << 0),
};

enum rts_color_coef_e {
	RTS_COLOR_COEF_BT601,
	RTS_COLOR_COEF_BT709,
	RTS_COLOR_COEF_USER_DEFINED
};

struct rts_color_coef_t {
	uint32_t coef_a;
	uint32_t coef_b;
	uint32_t coef_c;
	uint32_t coef_e;
	uint32_t coef_f;
};

#ifdef __cplusplus
}
#endif
#endif
