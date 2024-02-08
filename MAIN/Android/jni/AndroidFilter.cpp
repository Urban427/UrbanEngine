#include <jni.h>
#include <App.h>
#include <android/asset_manager.h>
#include <malloc.h>
#include "AndroidFileManager.h"
	#include "gles2/gl2.h"

extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_NativeLib_AndroidLogicCreate(
		JNIEnv * env,
		jobject java_obj) 
{
	
	glClearColor(0, 0, 1, 1);
}


extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_NativeLib_AndroidLogicUpdate(
		JNIEnv * env,
		jobject java_obj,
		jint width,
		jint height) 
{
	
}

extern "C" JNIEXPORT void JNICALL 
	Java_com_UrbanEngine_main_NativeLib_on_1touch_1press(
	JNIEnv * env,
	jobject java_obj,
	jfloat x,
	jfloat y)
{
	
}

extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_NativeLib_AndroidLogicDraw(
		JNIEnv * env,
		jobject java_obj) 
{
	
}