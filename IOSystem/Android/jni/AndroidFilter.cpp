#include <jni.h>
#include "PNG.h"
#include "AndroidFileManager.h"
#include <Color.h>
#include <GraphicsEngine.h>
#include "gles2/gl2.h"





Color color(1, 0, 0, 1);
GraphicsEngine graphicEngine;
VertexArrayObject* triangle;
Shader* shader;

extern "C" JNIEXPORT void JNICALL
	Java_com_UrbanEngine_main_RendererWrapper_AndroidLogicCreate(
		JNIEnv * env,
		jobject java_obj) 
{
	graphicEngine.clear(color);
	
	int height = 2408;
	int y = height / 4;
	
	int width = 1080;
	int x = width / 4;
	glViewport(-x, -y, width, height);
	
	const float triangleVertecles[] = {
		-0.5f, -0.5f, 0,
		1, 0, 0,
		
		 0.5f, -0.5f, 0,
		 0, 1, 0,
		 
		 0, 0.5f, 0,
		 0, 0, 1
	};
	
	VertexAttribute attributeList[] = {
		3,
		3
	};
	
	triangle = graphicEngine.createVertexArrayObject({
		(void*)triangleVertecles, sizeof(float) * (3 + 3),
		3,
		attributeList,
		2});
	
	shader = graphicEngine.createShaderProgram({ "../Assets/shader.vsh",  "../Assets/shader.fsh" });
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
	graphicEngine.clear();
	
	graphicEngine.setShaderProgram(shader);
	graphicEngine.setVertexArrayObject(triangle);
	graphicEngine.drawTriangles(triangle->getVertexBufferSize(), 0);
}

