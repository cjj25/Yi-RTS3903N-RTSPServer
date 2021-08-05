#ifndef __RTS_IO_GPIO_H__
#define __RTS_IO_GPIO_H__

/**
 *enum the gpio is requested or not
 *
 *this enum defined the using state of gpio
 */
enum rts_gpio_requested {
	GPIO_NOT_REQUESTED	= 0,	/**<no use*/
	GPIO_REQUESTED		= 1	/**<used*/
};

/**
 *enum the gpio direction
 *
 *this enum defined the direction of gpio
 */
enum rts_gpio_direct {
	GPIO_INPUT	= 0,	/**<input*/
	GPIO_OUTPUT	= 1	/**<output*/
};

/**
 *enum the gpio value
 *
 *this enum defined the value of gpio
 */
enum rts_gpio_value {
	GPIO_LOW	= 0,	/**<low*/
	GPIO_HIGH	= 1	/**<high*/
};

/**
 *enum the gpio domain
 *
 *this enum defined gpio domain
 */
enum rts_gpio_domain {
	SYSTEM_GPIO	= 0,	/**<system gpio*/
	MCU_GPIO	= 1,	/**<mcu gpio*/
	RTS_GPIO_DOMAIN_MAX
};

/**
 * struct rts_gpio - a structure describe a GPIO
 */
struct rts_gpio {
	int domain;	/**<the GPIO domain*/
	int gpio;	/**<the GPIO number*/
	int fd;		/**<the GPIO file descriptor*/
};

/**
 *get the using state of gpio
 *
 *@param domain		the gpio domain
 *@param gpio		the gpio number
 *@return the using state of gpio GPIO_NOT_REQUESTED: gpio has not be requested, GPIO_REQUESTED: gpio has be requested, <0:fail
 */
int rts_io_gpio_requested(int domain, int gpio);

/**
 *requst gpio
 *
 *@param domain		the gpio domain
 *@param gpio		the gpio number
 *@return the point of rts_gpio !NULL: success, NULL: fail
 */
struct rts_gpio *rts_io_gpio_request(int domain, int gpio);

/**
 *free gpio
 *
 *@param rts_gpio	the point of struct rts_gpio
 *@return 0: success, <0: fail
 */
int rts_io_gpio_free(struct rts_gpio *rts_gpio);

/**
 *set gpio value
 *
 *@param rts_gpio	the point of struct rts_gpio
 *@param value		the value you want to set
 *@return 0 : success, <0 : fail
 */
int rts_io_gpio_set_value(struct rts_gpio *rts_gpio, int val);

/**
 *get gpio value
 *
 *@param rts_gpio	the point of struct rts_gpio
 *@return the value of gpio 0: LOW, 1: HIGT, <0: fail
 */
int rts_io_gpio_get_value(struct rts_gpio *rts_gpio);

/**
 *get gpio value
 *
 *@param rts_gpio	the point of struct rts_gpio
 *@param dir		the direction you want to set
 *@return 0: success, <0: fail
 */
int rts_io_gpio_set_direction(struct rts_gpio *rts_gpio, int dir);

/**
 *get gpio direction
 *
 *@param rts_gpio	the point of struct rts_gpio
 *@return the direction of gpio 0: input, 1: output, <0: fail
 */
int rts_io_gpio_get_direction(struct rts_gpio *rts_gpio);

#endif
