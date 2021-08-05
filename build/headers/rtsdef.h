/*
 * Realtek Semiconductor Corp.
 *
 * librtscamkit/include/rtsdef.h
 *
 * Copyright (C) 2017      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _LIBRTSCAMKIT_RTSDEF_H
#define _LIBRTSCAMKIT_RTSDEF_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

enum {
	RTS_FALSE = 0,
	RTS_TRUE
};

struct rts_coordinate_t {
	int32_t x;
	int32_t y;
};

struct rts_size_t {
	uint32_t width;
	uint32_t height;
};

struct rts_rect_t {
	struct rts_coordinate_t start;
	struct rts_coordinate_t end;
};

struct rts_grid_size_t {
	uint32_t columns;
	uint32_t rows;
};

struct rts_grid_t {
	struct rts_coordinate_t start;
	struct rts_size_t cell;
	struct rts_grid_size_t size;
};

struct rts_buffer_t {
	void *vm_addr;
	uint32_t length;
};

struct rts_bitmap_t {
	uint32_t number;
	struct rts_buffer_t bitmap;
};

struct rts_point_con {
	int x;
	int y;
};

struct rts_point_res {
	struct rts_coordinate_t value;
	uint32_t res_width;
	uint32_t res_height;
};

#ifdef __cplusplus
}
#endif
#endif
