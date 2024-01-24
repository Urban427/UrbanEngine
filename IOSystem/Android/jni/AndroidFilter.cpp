#include <jni.h>
#include <App.h>
#include <android/asset_manager.h>
#include <malloc.h>
#include "../Filter/AndroidFileManager.h"

App app;
AndroidFileManager androidFileManager;

extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_NativeLib_AndroidLogicCreate(
		JNIEnv * env,
		jobject java_obj) 
{
	androidFileManager.init(env, &java_obj);
	app.onCreate();
}


extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_NativeLib_AndroidLogicUpdate(
		JNIEnv * env,
		jobject java_obj,
		jint width,
		jint height) 
{
	androidFileManager.init(env, &java_obj);
	app.setSize(width, height);
}

extern "C" JNIEXPORT void JNICALL 
	Java_com_UrbanEngine_main_NativeLib_on_1touch_1press(
	JNIEnv * env,
	jobject java_obj,
	jfloat x,
	jfloat y)
{
	/*
	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	AAsset* asset = AAssetManager_open(mgr, "test.txt", AASSET_MODE_UNKNOWN);
	if (asset == NULL)  {
		return;
	}
	long size = AAsset_getLength(asset);
	char* buffer = (char*)malloc(sizeof(char)*size);
	AAsset_read (asset,buffer,size);
	AAsset_close(asset);*/
	  
	app.Move();
}

extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_NativeLib_AndroidLogicDraw(
		JNIEnv * env,
		jobject java_obj) 
{
	app.onUpdate();
}

