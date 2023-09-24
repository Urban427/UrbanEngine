#include <jni.h>
#include <App.h>
#include "../Filter/AndroidFileManager.h"

App app;
AndroidFileManager androidFileManager;

extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicCreate(
		JNIEnv * env,
		jobject java_obj) 
{
	androidFileManager.init(env, &java_obj);
	app.onCreate();
}


extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicUpdate(
		JNIEnv * env,
		jobject java_obj,
		jint width,
		jint height) 
{
	androidFileManager.init(env, &java_obj);
	app.setSize(width, height);
}


extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicDraw(
		JNIEnv * env,
		jobject java_obj) 
{
	app.onUpdate();
}

