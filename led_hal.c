
#define LOG_TAG "LedHal"

/* 1. Declare a HMI structure */
/* 2. Declare an open function, return a led_device_t structure */
/* 3. Declare led_device_t structure */
/* 4. Reference by d:\tech\android\srcs\android-5.0.2\core\hardware\libhardware\modules\vibrator\Vibrator.c
*/

#include <hardware/led_hal.h>
#include <hardware/hardware.h>

#include <cutils/log.h>
#include <utils/Log.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>



static int fd;

static int led_open(struct led_device_t* dev)
{
	fd = open("/dev/leds", O_RDWR);
	//fd = open("/dev/young_leds", O_RDWR);	// error: there is no privilege for /dev/young_leds
	ALOGI("led_open : %d", fd);

	if (fd < 0)
		return -1;

	return 0;
}

/** Close this device */
static int led_close(struct hw_device_t* device)
{
	close(fd);
	return 0;
}

static int led_ctrl(struct led_device_t* dev, int whichLed, int ledStatus)
{
	int ret = ioctl(fd, ledStatus, whichLed);
	ALOGI("led_ctrl : %d, %d, %d", whichLed, ledStatus, ret);	
	return ret;
}

static struct led_device_t led_dev = {
	.common 	= {
		.close	= led_close,
	},

	.led_open 	= led_open,
	.led_ctrl	= led_ctrl,
};

static int led_device_open(const struct hw_module_t* module, const char* id,
		struct hw_device_t** device)
{
	*device = &led_dev;
	//*device = (hw_device_t *)led_dev;
	
	return 0;
}


/*===========================================================================*/
/* Default led HW module interface definition                           */
/*===========================================================================*/

static struct hw_module_methods_t led_module_methods = {
    .open = led_device_open,
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    //.tag = HARDWARE_MODULE_TAG,
    //.module_api_version = VIBRATOR_API_VERSION,
    //.hal_api_version = HARDWARE_HAL_API_VERSION,
    //.name = "Default vibrator HAL",
    //.author = "The Android Open Source Project",

    .id = "led",
    .methods = &led_module_methods,
};


