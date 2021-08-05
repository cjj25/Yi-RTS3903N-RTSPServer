/*
 * Realtek Semiconductor Corp.
 *
 * Copyright (C) 2014      Ming Qian<ming_qian@realsil.com.cn>
 */
#ifndef _RTS_CAMKIT_H
#define _RTS_CAMKIT_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include "rtsdef.h"
#include <rts_errno.h>
#include <rts_log.h>

#ifndef RTS_L_BYTE
#define RTS_L_BYTE(a)       ((a) & 0xff)
#endif
#ifndef RTS_H_BYTE
#define RTS_H_BYTE(a)       (((a) >> 8) & 0xff)
#endif
#ifndef RTS_L_WORD
#define RTS_L_WORD(a)       ((a) & 0xffff)
#endif
#ifndef RTS_H_WORD
#define RTS_H_WORD(a)       (((a) >> 16) & 0xffff)
#endif


#ifndef RTS_MAKE_WORD
#define RTS_MAKE_WORD(a, b) ((a) | ((b) << 8))
#endif
#ifndef RTS_MAKE_DWORD
#define RTS_MAKE_DWORD(a, b, c, d)  \
    ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))
#endif

#ifndef RTS_MAKE_WORD_BE
#define RTS_MAKE_WORD_BE(a, b)  ((b) | ((a) << 8))
#endif
#ifndef RTS_MAKE_DWORD_BE
#define RTS_MAKE_DWORD_BE(a, b, c, d)   \
    ((d) | ((c) << 8) | ((b) << 16) | ((a) << 24))
#endif

#ifndef RTS_SPLIT_WORD
#define RTS_SPLIT_WORD(array, value)    \
	do {\
		array[0] = (value) & 0xff;\
		array[1] = ((value) >> 8) & 0xff;\
	} while (0)
#endif
#ifndef RTS_SPLIT_DWORD
#define RTS_SPLIT_DWORD(array, value)   \
	do {\
		array[0] = (value) & 0xff;\
		array[1] = ((value) >> 8) & 0xff;\
		array[2] = ((value) >> 16) & 0xff;\
		array[3] = ((value) >> 24) & 0xff;\
	} while (0)
#endif

#ifndef RTS_SET_BIT
#define RTS_SET_BIT(v, i)   ((v) | (1<<(i)))
#endif
#ifndef RTS_CLEAR_BIT
#define RTS_CLEAR_BIT(v, i) ((v) & (~(1<<(i))))
#endif
#ifndef RTS_CHECK_BIT
#define RTS_CHECK_BIT(v, i) (((v)>>(i)) & 1)
#endif

#ifndef RTS_DIV_ROUND_UP
#define RTS_DIV_ROUND_UP(n, d)	(((n) + (d) - 1) / (d))
#endif

#ifndef RTS_DIV_ROUND_OFF
#define RTS_DIV_ROUND_OFF(n, d)	(((n) * 2 + (d)) / ((d) * 2))
#endif

#ifndef RTS_SAFE_DELETE
#define RTS_SAFE_DELETE(p)  \
        do { \
            if (p)\
                rts_free(p);\
            p = NULL;\
        } while (0)
#endif

#ifndef RTS_SAFE_RELEASE
#define RTS_SAFE_RELEASE(p, release)    \
        do { \
            if (p)\
                release(p);\
            p = NULL;\
        } while (0)
#endif

#ifndef RTS_SAFE_CLOSE
#define RTS_SAFE_CLOSE(fd, close_func)	\
	do { \
		if (fd >= 0) \
			close_func(fd);\
		fd = -1;\
	} while (0)
#endif

#ifndef RTS_ARRAY_SIZE
#define RTS_ARRAY_SIZE(array)   (sizeof(array) / sizeof((array)[0]))
#endif

#ifndef RTS_ARRSERT
#include <assert.h>
#define RTS_ASSERT(expr)    \
    if (!(expr)) {\
        RTS_ERR("fail to assert : %s\n", #expr);\
    }\
    assert(expr)
#endif

#define RTS_YUV_HEADER_SIZE         128

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:    the pointer to the member.
 * @type:   the type of the container struct this is embedded in.
 * @member: the name of the member within the struct.
 *
 */
#ifndef container_of
#define container_of(ptr, type, member) ({          \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

#ifndef RTS_SWAP
#define RTS_SWAP(a, b) do {\
	const typeof(a) tmp = a;\
	a = b;\
	b = tmp;\
} while (0)
#endif

#ifndef RTS_MAX
#define RTS_MAX(a, b) (a) > (b) ? (a) : (b)
#endif

#ifndef RTS_MIN
#define RTS_MIN(a, b) (a) < (b) ? (a) : (b)
#endif

#ifndef RTS_ALIGN
#define RTS_ALIGN(x, a)          (((x) + (a) - 1) & (~((a) - 1)))
#endif

struct rts_version_t {
	unsigned int major;
	unsigned int minor;
	unsigned int build;
	unsigned int reserved;
};

int rts_is_integer(const char *s);
long rts_get_file_size(const char *filename);
int rts_save_raw_data(const char *name, uint8_t *data, int length);
int rts_save_yuv_image(const char *name, uint8_t *data,
		       uint32_t width, uint32_t height, int length);
void rts_dump_trace(void);

void *__rts_malloc(size_t size, const char *func, int line);
void rts_free(void *ptr);
void *__rts_calloc(size_t nmemb, size_t size, const char *func, int line);
void *__rts_realloc(void *ptr, size_t size, const char *func, int line);

#define rts_malloc(size)	__rts_malloc(size, __func__, __LINE__)
#define rts_calloc(nmemb, size)	__rts_calloc(nmemb, size, __func__, __LINE__)
#define rts_realloc(ptr, size)	__rts_realloc(ptr, size, __func__, __LINE__)

#define RTS_CALLOC_ARRAY(ptr, nmemb)	(ptr = rts_calloc(nmemb, sizeof(*ptr)))
#define RTS_CALLOC_STRU(ptr)		RTS_CALLOC_ARRAY(ptr, 1)

#define RTS_S_C_VAR(var, new_value, type)	\
	do {\
		type *ptr = (type *)&var;\
		*ptr = new_value;\
	} while (0)

#define RTS_VALID_STEPWISE_VALUE(val, min, max, step) \
	do {\
		if (val < (min))\
			val = (min);\
		else if (val > (max)) \
			val = (max);\
		else if ((step) && ((val - (min)) % (step))) \
			val -= ((val - (min)) % (step));\
	} while (0)

int rts_test_bit(uint8_t *ptr, size_t size, int nr);
void rts_set_bit(uint8_t *ptr, size_t size, int nr);
void rts_clear_bit(uint8_t *ptr, size_t size, int nr);
void rts_change_bit(uint8_t *ptr, size_t size, int nr);
uint32_t rts_get_bits_val(uint8_t *ptr, size_t size, int nr, int count);
void rts_set_bits_val(uint8_t *ptr, size_t size, int nr, int count,
		      uint32_t val);
void rts_negate_bits(uint8_t *ptr, size_t size);
int rts_buffer_test_bit(struct rts_buffer_t *buffer, int nr);
void rts_buffer_set_bit(struct rts_buffer_t *buffer, int nr);
void rts_buffer_clear_bit(struct rts_buffer_t *buffer, int nr);
void rts_buffer_change_bit(struct rts_buffer_t *buffer, int nr);
uint32_t rts_buffer_get_bits_val(struct rts_buffer_t *buffer,
				 int nr, int count);
void rts_buffer_set_bits_val(struct rts_buffer_t *buffer,
			     int nr, int count, uint32_t val);
void rts_buffer_negate(struct rts_buffer_t *buffer);

#define RTS_MSEC_PER_SEC		1000L
#define RTS_USEC_PER_MSEC		1000L
#define RTS_NSEC_PER_USEC		1000L
#define RTS_NSEC_PER_MSEC		1000000L
#define RTS_USEC_PER_SEC		1000000L
#define RTS_NSEC_PER_SEC		1000000000L

uint64_t rts_get_realtime_time(void);
uint64_t rts_get_monotonic_time(void);
uint64_t rts_get_monotonic_raw_time(void);

unsigned long rts_memweight(uint8_t *pdata, unsigned int size);
unsigned long rts_memweight_v2(uint8_t *pdata, unsigned int size, uint32_t num);

int rts_alloc_bitmap(struct rts_bitmap_t *bitmap, uint32_t number);
void rts_free_bitmap(struct rts_bitmap_t *bitmap);
int rts_alloc_buffer(struct rts_buffer_t *buffer, uint32_t length);
void rts_free_buffer(struct rts_buffer_t *buffer);

int rts_pollin(int fd, int timeout);
void rts_delay(uint64_t usec);

#ifndef atomic_inc
#define atomic_inc(x) __sync_add_and_fetch((x), 1)
#endif
#ifndef atomic_dec
#define atomic_dec(x) __sync_sub_and_fetch((x), 1)
#endif
#ifndef atomic_add
#define atomic_add(x, y) __sync_add_and_fetch((x), (y))
#endif
#ifndef atomic_sub
#define atomic_sub(x, y) __sync_sub_and_fetch((x), (y))
#endif

#endif
