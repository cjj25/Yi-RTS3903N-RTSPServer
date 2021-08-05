/*
 * Realtek Semiconductor Corp.
 *
 * libs/include/rtsutils.h
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _LIBS_INCLUDE_RTSUTILS_H
#define _LIBS_INCLUDE_RTSUTILS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define RTS_RAW_HEADER_LENGTH       128

struct rts_raw_t {
	uint8_t header[RTS_RAW_HEADER_LENGTH];
	uint32_t length;
	uint8_t *pdata;
	uint32_t width;
	uint32_t height;
	uint32_t fmt;
	unsigned int snr_fmt;
	unsigned int raw_fmt;
	int streamid;
	int fd;
	int initialized;
	int skip_count;
	void (*make_raw_data)(struct rts_raw_t *praw, uint8_t *pdata);
};

int rts_init_raw(unsigned int raw_fmt, struct rts_raw_t **ppraw);
void rts_release_raw(struct rts_raw_t *praw);
int rts_get_raw_frame(struct rts_raw_t *praw);
int rts_get_raw_header(struct rts_raw_t *praw);
int rts_update_raw_fmt(unsigned int raw_fmt, struct rts_raw_t *praw);

#ifdef __cplusplus
}
#endif
#endif
