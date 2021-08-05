/*
 * Realtek Semiconductor Corp.
 *
 * include/rtsosd2.h
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _INCLUDE_RTSOSD2_H
#define _INCLUDE_RTSOSD2_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <rtsisp_def.h>
#include <rtsdef.h>

typedef const void *RtsOsd2Inst;

struct rts_osd2_config {
	int format;
	uint32_t width;
	uint32_t height;
};

struct rts_osd2_blk {
	struct rts_rect_t area;
	int pixel_fmt;
	void *pdata;
	uint32_t length;
	uint32_t fixed_buf_len;

	/* it is valid when pixel_fmt is set to RTS_PIX_FMT_1BPP */
	uint32_t pure_color;
};

struct rts_osd2_attr_t {
	int flick_enable;
	uint32_t show_num;
	uint32_t hide_num;
};

struct rts_osd2_encin {
	uint32_t bus_luma;
	uint32_t bus_chroma;
	void *pbuf;
	uint32_t buf_size;
};

int rts_osd2_init(RtsOsd2Inst *posd, struct rts_osd2_config *config);
int rts_osd2_release(RtsOsd2Inst posd);
int rts_osd2_update(RtsOsd2Inst posd,
		  struct rts_osd2_config *config);
int rts_osd2_config_block(RtsOsd2Inst posd,
			  int blkidx, struct rts_osd2_blk *block);
int rts_osd2_enable_block(RtsOsd2Inst posd, int blkidx);
int rts_osd2_disable_block(RtsOsd2Inst posd, int blkidx);
int rts_osd2_get_attr(RtsOsd2Inst posd,
		      int blkidx, struct rts_osd2_attr_t *attr);
int rts_osd2_set_attr(RtsOsd2Inst posd,
		      int blkidx, struct rts_osd2_attr_t *attr);
int rts_osd2_encode(RtsOsd2Inst posd, struct rts_osd2_encin *frame);
int rts_osd2_set_color_table(RtsOsd2Inst posd, int fmt, uint32_t val,
			     uint8_t red, uint8_t green, uint8_t blue,
			     uint8_t alpha);
uint32_t rts_osd2_get_color_table(RtsOsd2Inst posd, int fmt,
				  uint8_t red, uint8_t green, uint8_t blue,
				  uint8_t alpha);
int rts_osd2_query_block(RtsOsd2Inst posd, int blkidx,
			 struct rts_osd2_blk *block, uint8_t *enable);
int rts_osd2_get_blk_max_num(void);
void rts_osd2_set_adma_copy(RtsOsd2Inst posd, int enable);
int rts_osd2_get_adma_copy(RtsOsd2Inst posd);

int rts_osd2_set_epoll_hook(RtsOsd2Inst posd, void *master,
			    int (*hook_func)(void *master, int fd));
int rts_osd2_check_done(RtsOsd2Inst posd);
int rts_osd2_make_rdy(RtsOsd2Inst posd);
int rts_osd2_use_sigio(RtsOsd2Inst posd, int sigio_need);
#ifdef __cplusplus
}
#endif
#endif
