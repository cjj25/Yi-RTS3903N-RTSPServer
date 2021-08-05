/*
 * Realtek Semiconductor Corp.
 *
 * include/rtsisp_hwver.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _INCLUDE_RTSISP_HWVER_H
#define _INCLUDE_RTSISP_HWVER_H

#include <stdint.h>

extern struct rts_isp_hw_id rts_hw_id;

enum {
	RTS_HW_ID_VER_UNKNOWN = 0,
	RTS_HW_ID_VER_RLE0745,
	RTS_HW_ID_VER_RTS3901,
	RTS_HW_ID_VER_RTS3903,
};

enum {
	RTS_HW_ID_REV_UNKNOWN = 0,
	RTS_HW_ID_REV_A,
	RTS_HW_ID_REV_B,
	RTS_HW_ID_REV_C
};

struct rts_isp_hw_id {
	uint16_t hw_ver;
	uint16_t hw_rev;
};

struct rts_isp_hw_id rts_get_hw_id();

#endif
