/*!
 * \mainpage librtsio API reference
 *
 * \section Introduction
 *
 * librtsio is a library that helps you to develop your io application using realtek's soc camera
 *
 * \section features
 *
 * 1.get sar adc value
 *
 * 2.get/set gpio configuration
 *
 * 3.i2c read/write
 *
 * \section start
 *
 * Some example programs can be found in the examples subdirectory
 *
 * \example io_example.c
 *
 * Realtek Semiconductor Corp.
 *
 * Copyright (C) 2016      steven_feng<steven_feng@realsil.com.cn>
 *
 */
#ifndef __RTS_IO_ADC_H__
#define __RTS_IO_ADC_H__

/**
 *enum the adc channel
 *
 *this enum defined the adc channel witch maybe used
 */
enum rts_adc_channel {
	ADC_CHANNEL_0	= 0,	/**<channel 0*/
	ADC_CHANNEL_1	= 1,	/**<channel 1*/
	ADC_CHANNEL_2	= 2,	/**<channel 2*/
	ADC_CHANNEL_3	= 3,	/**<channel 3*/
};

/**
 *get adc value
 *
 *@param:	adc_channel the adc channel witch you want read
 *@return the value of adc_channel
 */
int rts_io_adc_get_value(int adc_channel);
#endif
