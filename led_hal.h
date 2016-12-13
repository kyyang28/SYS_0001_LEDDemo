#ifndef ANDROID_LED_INTERFACE_H
#define ANDROID_LED_INTERFACE_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <hardware/hardware.h>

__BEGIN_DECLS

struct led_device_t {
    /**
     * Common methods of the led device.  This *must* be the first member of
     * led_device_t as users of this structure will cast a hw_device_t to
     * led_device_t pointer in contexts where it's known the hw_device_t references a
     * led_device_t.
     */
    struct hw_device_t common;

    /**
     * Set the provided functions to led
     *
     * led_open(), led_ctrl()
     * led_close() is in common
     */
	int (*led_open)(struct led_device_t* dev);
	int (*led_ctrl)(struct led_device_t* dev, int whichLed, int ledStatus);
};

__END_DECLS

#endif  // ANDROID_LED_INTERFACE_H

