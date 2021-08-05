/*
 * Realtek Semiconductor Corp.
 *
 * include/rtsisp_def.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _INCLUDE_RTSISP_DEF_H
#define _INCLUDE_RTSISP_DEF_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "rtsdef.h"

#define RTS_ISP_AE_GAIN_UNIT		256

enum {
	RTS_ISP_BUF_COHERENT = 0,
	RTS_ISP_BUF_FROM_DEVICE = 1,
	RTS_ISP_BUF_TO_DEVICE = 2,
	RTS_ISP_BUF_BIDIRECTIONAL = 3,
};

struct rts_isp_dma_buffer {
	void *vm_addr;
	uint32_t length;
	uint32_t phy_addr;
	uint32_t buf_io;
	uint8_t direction;
};

enum {
	RTS_ISP_DMA_BUFFER_FROM_HEAD,
	RTS_ISP_DMA_BUFFER_FROM_END,
};

enum rts_isp_blk_type {
	RTS_ISP_BLK_TYPE_UNDEFINED = 0,
	RTS_ISP_BLK_TYPE_RECT = 1,
	RTS_ISP_BLK_TYPE_GRID,
};

struct rts_isp_ae_gain {
	uint16_t analog;
	uint16_t digital;
	uint16_t isp_digital;
};

struct rts_isp_ae_weight {
	uint32_t window_num;
	uint8_t *weights;
};

struct rts_isp_ae_statis {
	uint8_t y_mean;
	uint32_t window_num;
	uint8_t *y_means;
	uint32_t histogram_num;
	uint16_t *statis;
};

struct rts_isp_awb_statis {
	uint32_t window_num;
	uint8_t *r_means;
	uint8_t *g_means;
	uint8_t *b_means;
};

struct rts_isp_af_statis {
	uint32_t whole_win_sum;
	uint32_t center_win_sum;
	uint32_t window_num;
	uint32_t *win_sum;
};

struct rts_isp_awb_ct_gain {
	uint8_t r_gain;
	uint8_t b_gain;
};

struct rts_isp_awb_auto_gain_adjustment {
	uint16_t r_gain;
	uint16_t b_gain;
};

enum {
	RTS_ISP_PWR_FREQUENCY_DISABLED = 0,
	RTS_ISP_PWR_FREQUENCY_50HZ = 1,
	RTS_ISP_PWR_FREQUENCY_60HZ = 2,
	RTS_ISP_PWR_FREQUENCY_AUTO = 3
};

enum rts_isp_md_data_type {
	RTS_ISP_MD_DATA_TYPE_AVGY = 0,
	RTS_ISP_MD_DATA_TYPE_RLTPRE,
	RTS_ISP_MD_DATA_TYPE_RLTCUR,
	RTS_ISP_MD_DATA_TYPE_BACKY,
	RTS_ISP_MD_DATA_TYPE_BACKF,
	RTS_ISP_MD_DATA_TYPE_BACKC,
	RTS_ISP_MD_DATA_TYPE_RESERVED
};

enum rts_isp_md_detect_mode {
	RTS_ISP_MD_MODE_USER_TRIG = 0,
	RTS_ISP_MD_MODE_HW_DETECT,
	RTS_ISP_MD_MODE_RESERVED
};

struct rts_isp_md_data {
	struct rts_isp_dma_buffer datas[RTS_ISP_MD_DATA_TYPE_RESERVED];
};

struct rts_isp_md_line_area {
	uint8_t k;
	int16_t b[4];
};

struct rts_isp_md_line_result {
	unsigned int number;
	struct rts_coordinate_t coords[6];
};

#define RTS_ISP_VIDEO_ID_OFFSET		51

#ifdef __cplusplus
}
#endif
#endif
