/*
 * Realtek Semiconductor Corp.
 *
 * librtsbmp/include/rtsbmp.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _LIBRTSBMP_INCLUDE_RTSBMP_H
#define _LIBRTSBMP_INCLUDE_RTSBMP_H

#include <stdint.h>
#include <rtscolor.h>

enum {
	RTS_BMP_BITS_DATA_CONTINUOUS = 0,
	RTS_BMP_BITS_DATA_BYTE_ALIGN,
	RTS_BMP_BITS_DATA_LINE_ALIGN
};

struct rts_bmp_encin {
	uint8_t *psrc;
	int length;
	int fmt;
	uint32_t width;
	uint32_t height;
	int align;
};

int rts_bmp_encode(struct rts_bmp_encin *encin, uint8_t *pdst, int dst_len);
int rts_bmp_save(struct rts_bmp_encin *encin, const char *filename);

#endif
