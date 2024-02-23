#include <jni.h>
#include <App.h>
#include <malloc.h>
#include "AndroidFileManager.h"

App app;

extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_NativeLib_AndroidLogicCreate(
		JNIEnv * env,
		jobject java_obj) 
{
	FileManager::init(env, &java_obj);
	app.onCreate();
}


extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_NativeLib_AndroidLogicUpdate(
		JNIEnv * env,
		jobject java_obj,
		jint width,
		jint height) 
{
	app.setSize(width, height);
}

extern "C" JNIEXPORT void JNICALL 
	Java_com_UrbanEngine_main_NativeLib_on_1touch_1press(
	JNIEnv * env,
	jobject java_obj,
	jfloat x,
	jfloat y)
{
	app.Move();
}

extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_NativeLib_AndroidLogicDraw(
		JNIEnv * env,
		jobject java_obj) 
{
	app.onUpdate();
}