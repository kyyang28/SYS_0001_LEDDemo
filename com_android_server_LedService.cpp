
#define LOG_TAG "LedService"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <hardware/led_hal.h>

//#include <android/log.h>	/* liblog */

namespace android
{

static led_device_t* led_device;

jint c_ledOpen(JNIEnv *env, jobject cls)
{
	jint err;
    hw_module_t* module;
	hw_device_t* device;

	ALOGI("native c_ledOpen ...");

	/* 1. hw_get_module */
    err = hw_get_module("led", (hw_module_t const**)&module);
	
    if (err == 0) {
		/* 2. get_device() ==> module->methods->open(module, name, &device) */
		err = module->methods->open(module, NULL, &device);
		if (err == 0) {			
			/* 3. call led_open() function */
			led_device = (led_device_t *)device;
			return led_device->led_open(led_device);
		} else {
			return -1;
		}
    }	
		
	return -1;
}

void c_ledClose(JNIEnv *env, jobject cls)
{
	//ALOGI("native c_ledClose ...");
	//close(fd);
}

jint c_ledCtrl(JNIEnv *env, jobject cls, jint whichLed, jint ledStatus)
{
	ALOGI("native c_ledCtrl %d, %d", whichLed, ledStatus);
	return led_device->led_ctrl(led_device, whichLed, ledStatus);
}

static const JNINativeMethod method_table[] = {
	{ "native_ledOpen", "()I", (void *)c_ledOpen },	// () means no parameter, V means return type void
	{ "native_ledClose", "()V", (void *)c_ledClose }, // () means no parameter, V means return type void
	{ "native_ledCtrl", "(II)I", (void *)c_ledCtrl }, // () means no parameter, V means return type void
};

int register_android_server_LedService(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "com/android/server/LedService",
            method_table, NELEM(method_table));
}

};

