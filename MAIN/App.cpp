#include "App.h"
#include "Color.h"
#include "Matrix4x4.h"
#include "FileManager.h"
#include "Rect.h"

#include <math.h>
#include <malloc.h>

App::App()
{
}

App::~App()
{
}

struct Vertex
{
	Vector3 pos;
	Vector2 ui;
};

void App::onCreate()
{
	_running = true;
	if (ioSystem.onCreate()) {
		_running = false;
	}
	
	
	int width;
	int height;
	FileData* f = openFile(ghost2.b);
	readFile(&width, sizeof(int), 1, f);
	readFile(&height, sizeof(int), 1, f);
	unsigned int* image = (unsigned int*)malloc(width * height* sizeof(int));
	for(int i = 0; i < width * height; i++)
	{
		readFile(&image[i], sizeof(int), 1, f);
	}
	//closeFile(f);
	
	graphicEngine.init();
	//graphicEngine.setViewPort(ioSystem.getInnerSize());
	graphicEngine.clear(Color(1, 0, 0, 1));
	graphicEngine.setCullMode(FrontFace);

	unsigned int indeces[] = {
		0,1,2,
		0,2,3,
		
		4,7,6,
		4,6,5,
		
		0,4,5,
		0,5,1,
		
		1,5,6,
		1,6,2,
		
		2,6,7,
		2,7,3,
		
		4,0,3,
		4,3,7,
	};
	
	
	indexes = graphicEngine.createIndexArrayObject({
		indeces, 
		sizeof(indeces) / sizeof(int)});


	Vector3 positionList[] = 
	{
		Vector3( 0.5f,-0.5f,-0.5f),
		Vector3( 0.5f,-0.5f, 0.5f),
		Vector3(-0.5f,-0.5f, 0.5f),
		Vector3(-0.5f,-0.5f,-0.5f),

		//back face
		Vector3( 0.5f, 0.5f,-0.5f),
		Vector3( 0.5f, 0.5f, 0.5f),
		Vector3(-0.5f, 0.5f, 0.5f),
		Vector3(-0.5f, 0.5f,-0.5f),
	};

	Vector2 texcoordsList[] = {
		Vector2(0, 0),
		Vector2(0, 1),
		Vector2(1, 0),
		Vector2(1, 1),
		
	};

	Vertex triangleVertecles[] = {
		{positionList[0], texcoordsList[1]},
		{positionList[1], texcoordsList[0]},
		{positionList[2], texcoordsList[2]},
		{positionList[3], texcoordsList[3]},
		
		{positionList[4], texcoordsList[0]},
		{positionList[5], texcoordsList[2]},
		{positionList[6], texcoordsList[3]},
		{positionList[7], texcoordsList[1]},
	};
	
	triangle = graphicEngine.createVertexArrayObject({ 
	(void*)triangleVertecles, 
	sizeof(Vertex),
	sizeof(triangleVertecles) / sizeof(Vertex)
	});
	
	
	shader = graphicEngine.createShaderProgram({ "../Assets/shader.vsh",  "../Assets/shader.fsh" });
	
	uniform = graphicEngine.createUniformObject({
		shader->getID(),
		"u_TextureUnit",
		0
	});
	
	texture = graphicEngine.createTexture({
		(unsigned int)width,
		(unsigned int)height,
		image
	});
}

void  App::setSize(unsigned int width, unsigned int height)
{
	ioSystem.setSize(width, height);
}

void App::onUpdate()
{
	scale += 0.003f;
	
	Rect size = ioSystem.getInnerSize();
	Matrix4x4 camView, temp;
	camView.setIdentity();
	camView.setRotationY(sin(-scale) * 1.14f);
	
	
	temp.setIdentity();
	temp.setTranslation(Vector3(sin(scale) * 3, 1, cos(scale) * 3));
	camView *= temp;
	
	camView.inverse();
	
	
	Matrix4x4 projection;
	projection.setIdentity();
	//projection.setOrthoLH(size.width * 0.004f, size.height * 0.004f, -4, 4);
	projection.setPerspectiveFovLH(
	1.57f, 
	(float)size.width / (float)size.height,
	0.1f, 111);
	
	Matrix4x4 world;
	world.setIdentity();
	//world.setRotationX(scale * 3.14f);
	
	temp.setIdentity();
	//temp.setRotationY(scale * 3.14f);
	world *= temp;
	
	temp.setIdentity();
	//temp.setRotationZ(scale * 3.14f);
	world *= temp;
	
	temp.setIdentity();
	//temp.setScale(Vector3(2, 2, 1));
	world *= temp;
	
	temp.setIdentity();
	temp.setTranslation(Vector3(0, 0, -5));
	world *= temp;
	
	world *= camView;
	
	graphicEngine.setMatrix(shader, world);
	graphicEngine.setProjectionMatrix(shader, projection);
	
	
	
	graphicEngine.clear();
	
	graphicEngine.setShaderProgram(shader);
	graphicEngine.setTexture(texture);
	uniform->setValue(0);
	graphicEngine.setVertexArrayObject(triangle);
	graphicEngine.setIndexArrayObject(indexes);
	graphicEngine.drawTriangles(indexes->getSize());
	
	
	if (ioSystem.onUpdate()) {
		_running = false;
	}
}

bool App::isRunning()
{
	return _running;
}
