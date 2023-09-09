#include <jni.h>
#include <malloc.h>
#include "gl2.h"
#include "PNG.h"
#include "AndroidFileManager.h"
#include <GraphicsEngine.h>





GraphicsEngine graphicEngine;

extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicCreate(
		JNIEnv * env,
		jobject java_obj) 
{
	
}

void AndroidLogicUpdate()
{
	//VertexBufferData d;
	//VertexArrayObject vbo(d);
}


extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicUpdate(
		JNIEnv * env,
		jobject java_obj) 
{
	
}


extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicDraw(
		JNIEnv * env,
		jobject java_obj) 
{
	
}

