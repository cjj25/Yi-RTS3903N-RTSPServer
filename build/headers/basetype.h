/*------------------------------------------------------------------------------
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                                                                            --
--                            Hantro Products Oy.                             --
--                                                                            --
--                   (C) COPYRIGHT 2006 HANTRO PRODUCTS OY                    --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
--------------------------------------------------------------------------------
--
--  Description : Basic type definitions.
--
------------------------------------------------------------------------------*/

#ifndef BASETYPE_H_INCLUDED
#define BASETYPE_H_INCLUDED

#include <stdint.h>

#define VOLATILE    volatile

#ifdef __linux__    /* typedefs for Linux */

#include <stddef.h> /* for size_t, NULL, etc. */

typedef unsigned char u8;
typedef signed char i8;
typedef unsigned short u16;
typedef signed short i16;
typedef unsigned int u32;
typedef signed int i32;
typedef unsigned long long u64;
typedef int64_t   i64;

typedef size_t ptr_t;

#ifdef ADDRESS_WIDTH_64
#define PRT_PTR "lx"
#else
#define PRT_PTR "x"
#endif

#ifndef __cplusplus
typedef enum {
        false   = 0,
        true    = 1
} bool;
#endif

#else /* __symbian__ or __win__ or whatever, customize it to suit well */

#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;

#define _SIZE_T_DEFINED
#endif

#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else /*  */
#define NULL    ((void *)0)
#endif /*  */
#endif

typedef unsigned char u8;
typedef signed char i8;
typedef unsigned short u16;
typedef signed short i16;
typedef unsigned int u32;
typedef signed int i32;
typedef unsigned long long u64;
typedef int64_t   i64;


#ifndef __cplusplus
typedef enum {
        false   = 0,
        true    = 1
} bool;
#endif

#endif

#if defined(VC1SWDEC_16BIT) || defined(MP4ENC_ARM11)
typedef unsigned short u16x;
typedef signed short i16x;
#else
typedef unsigned int u16x;
typedef signed int i16x;
#endif

#endif /* BASETYPE_H_INCLUDED */
