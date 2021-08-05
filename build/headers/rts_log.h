/*
 * Realtek Semiconductor Corp.
 *
 * librtscamkit/rts_log.h
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _LIBRTSCAMKIT_RTS_LOG_H
#define _LIBRTSCAMKIT_RTS_LOG_H

#include <stdint.h>
#include <stdarg.h>

enum RTS_LOG_TYPE {
	RTS_LOG_IDX_CONS = 0,
	RTS_LOG_IDX_SYSLOG,
	RTS_LOG_IDX_FILE,
	RTS_LOG_IDX_CALLBACK,
	RTS_LOG_IDX_RESERVED
};

enum RTS_LOG_MASK {
	RTS_LOG_MASK_CONS = (0x1 << RTS_LOG_IDX_CONS),
	RTS_LOG_MASK_SYSLOG = (0x1 << RTS_LOG_IDX_SYSLOG),
	RTS_LOG_MASK_FILE = (0x1 << RTS_LOG_IDX_FILE),
	RTS_LOG_MASK_CALLBACK = (0x1 << RTS_LOG_IDX_CALLBACK),
};

enum RTS_LOG_PRIORITY {
	RTS_LOG_DEBUG = 0,
	RTS_LOG_INFO,
	RTS_LOG_NOTICE,
	RTS_LOG_WARNING,
	RTS_LOG_ERR,
	RTS_LOG_CRIT,
	RTS_LOG_ALERT,
	RTS_LOG_EMERG,
	RTS_LOG_MEM,
	RTS_LOG_REG,
	RTS_LOG_RESERVED
};

/*
 * rts_log :
 * */
void rts_log(int priority, const char *format, ...);

/*
 * rts_set_log_ident :
 * */
int rts_set_log_ident(const char *ident);

/*
 * rts_set_log_mask :
 *
 * @mask : If the mask argument is 0, the current log mask is not modified
 *
 * return value : the current log_mask
 *
 * */
uint32_t rts_set_log_mask(uint32_t mask);
uint32_t rts_get_log_mask(void);
uint32_t rts_clr_log_mask(void);

/*
 * rts_set_log_file :
 *
 * @filename : NULL will close log file
 *
 * return value: 0 success, others fail
 *
 * */
int rts_set_log_file(const char *filename);

int rts_set_log_callback(void (*callback)(const char *, va_list));

/*
 * rts_set_log_level
 *
 * @level_mask : If the level_mask argument is 0, the current level_mask is not modified.
 *
 * return value : the current level_mask
 *
 * */
uint32_t rts_set_log_level(uint32_t level_mask);
uint32_t rts_get_log_level(void);
uint32_t rts_clr_log_level(void);

int rts_set_log_enable(int priority, int enable);
int rts_get_log_enable(int priority, int enable);

/*
 * rts_dump_data :
 * */
void rts_dump_data(char *data, unsigned int len, unsigned int row);

#ifdef RTS_LOG_TAG
#define _TAG	" ["RTS_LOG_TAG"] "
#else
#define _TAG	""
#endif

#define __RTS_LOG(level, fmt, arg...) \
	rts_log(level, _TAG"<%s, %d>"fmt, __func__, __LINE__, ##arg)

#define RTS_LOG(level, fmt, arg...) \
	rts_log(level, _TAG""fmt, ##arg)

#define RTS_DEBUG(...) \
	do {\
		rts_log(RTS_LOG_DEBUG, _TAG""__VA_ARGS__);\
	} while (0)

#define RTS_INFO(...) \
	do {\
		rts_log(RTS_LOG_INFO, _TAG""__VA_ARGS__);\
	} while (0)

#define RTS_NOTICE(...) \
	do {\
		__RTS_LOG(RTS_LOG_NOTICE, __VA_ARGS__);\
	} while (0)

#define RTS_WARNING(...) \
	do {\
		__RTS_LOG(RTS_LOG_WARNING, __VA_ARGS__);\
	} while (0)

#define RTS_ERR(...) \
	do {\
		__RTS_LOG(RTS_LOG_ERR, __VA_ARGS__);\
	} while (0)

#define RTS_CRIT(...) \
	do {\
		__RTS_LOG(RTS_LOG_CRIT, __VA_ARGS__);\
	} while (0)

#define RTS_ALERT(...) \
	do {\
		__RTS_LOG(RTS_LOG_ALERT, __VA_ARGS__);\
	} while (0)

#define RTS_EMERG(...) \
	do {\
		__RTS_LOG(RTS_LOG_EMERG, __VA_ARGS__);\
	} while (0)

#define RTS_OPT(...) \
	do {\
		fprintf(stdout, __VA_ARGS__);\
	} while (0)

#endif
