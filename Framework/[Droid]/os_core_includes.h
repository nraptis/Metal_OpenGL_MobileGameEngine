#ifndef CORE_INCLUDES_ANDROID_H
#define CORE_INCLUDES_ANDROID_H

#include "os_core_outlets.h"

#include <android/log.h>
#include <android/sensor.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <jni.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <GLES/gl.h>

extern JNIEnv *gJNIEnv;
extern JavaVM *gJVM;

extern jobject _objJNIHelper;
extern jclass _clsJNIHelper;


#endif
