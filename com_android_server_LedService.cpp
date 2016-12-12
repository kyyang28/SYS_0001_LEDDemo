
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

//#include <android/log.h>	/* liblog */

namespace android
{

static jint fd;

jint c_ledOpen(JNIEnv *env, jobject cls)
{
	fd = open("/dev/leds", O_RDWR);
	//fd = open("/dev/young_leds", O_RDWR);	// error: there is no privilege for /dev/young_leds
	ALOGI("LEDDemo", "native c_ledOpen : %d", fd);

	if (fd < 0)
		return -1;

	return 0;
}

void c_ledClose(JNIEnv *env, jobject cls)
{
	ALOGI("native c_ledClose ...\n");

	close(fd);
}

jint c_ledCtrl(JNIEnv *env, jobject cls, jint whichLed, jint ledStatus)
{
	int ret = ioctl(fd, ledStatus, whichLed);
	
	ALOGI("native c_ledCtrl : %d, %d, %d", whichLed, ledStatus, ret);
	
	return ret;
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

