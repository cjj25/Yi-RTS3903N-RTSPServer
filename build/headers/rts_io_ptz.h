/*************************************************************************
    > File Name: io.h
    > Author: steven_feng
    > Mail: steven_feng@realsil.com.cn
    > Created Time: 2015/03/27
 ************************************************************************/
#ifndef __RTS_IO_H__
#define __RTS_IO_H__
#include <stdint.h>
#define CAMERAID	0x01

enum ptz_direct {
	PTZ_STOP       =   0x00,
	PTZ_RIGHT      =   0x02,
	PTZ_LEFT       =   0x04,
	PTZ_UP         =   0x08,
	PTZ_DOWN       =   0x10,
};

enum ptz_speed {
	PTZ_SLOWEST    =   0x0B,
	PTZ_SLOW       =   0x14,
	PTZ_NOMAL      =   0x20,
	PTZ_FAST       =   0x2A,
	PTZ_FASTEST    =   0x3F,
};

int rts_io_ptz_running(uint8_t chdir);
int rts_io_ptz_running_angle(uint8_t chdir, uint16_t angle);
int rts_io_ptz_set_speed(uint8_t level);
int rts_io_ptz_get_speed();
int rts_io_ptz_create_preset();
int rts_io_ptz_run_preset();
int rts_io_ptz_del_preset();

#endif
