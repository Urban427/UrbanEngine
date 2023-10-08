#include "App.h"
#include "Color.h"
#include "Matrix4x4.h"
#include "FileManager.h"
#include "Rect.h"
#include "Math.h"

#include <math.h>
#include <cmath>
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
	FileData* f = openFile(0012.b);
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
	graphicEngine.clear(Color(1, 1, 1, 1));
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
	
	
	void (*functions[])(float* array, unsigned int size) = {
		generateIncreasingArray, 	 //0
		generateLowingArray,		 //1
		generateSquaredArray,		 //2
		generateSawArray,		 	 //3
		generateSinusArray,		 	 //4
		generateStepsArray,			 //5
		randomArray,		 		 //6
		randomArray2,				 //7
	};
	
	unsigned int numberOfSqueresArray[] = {
		5 * 50,
		10 * 1000000,
		50 * 1000000,
	};
	
	circlesToDraw = 50000000;
	numberOfSqueres = numberOfSqueresArray[0];
	drawLines = 0;
	
	setSeed(33);
	x = (float*)malloc(sizeof(float) * numberOfSqueres);
	y = (float*)malloc(sizeof(float) * numberOfSqueres);


	/*
	x = (float*)malloc(sizeof(float) * 3);
	y = (float*)malloc(sizeof(float) * 3);
	for(int i = 0; i < 3; i++)
	{
		ioSystem.initTime();
		functions[6](_x, numberOfSqueresArray[i]);
		double t = ioSystem.getDeltaTime();
		y[i] = (t / 10) * 0.8f + 0.1f;
		x[i] = ((float)numberOfSqueresArray[i] / 60000000) * 0.8f + 0.1f;
	}*/
	
	
	functions[6](x, numberOfSqueres);
	functions[7](y, numberOfSqueres);
	
	normalizePoints(x, numberOfSqueres);
	normalizePoints(y, numberOfSqueres);
	//saveFileData(x, numberOfSqueres);
	
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
	//camView.setRotationY(sin(-scale) * 1.14f);
	
	
	temp.setIdentity();
	//temp.setTranslation(Vector3(sin(scale) * 3, 1, cos(scale) * 3));
	camView *= temp;
	
	camView.inverse();
	
	
	Matrix4x4 projection;
	projection.setIdentity();
	//projection.setOrthoLH(size.width * 0.004f, size.height * 0.004f, -4, 4);
	//projection.setPerspectiveFovLH(
	//1.57f, 
	//(float)size.width / (float)size.height,
	//0.1f, 111);
	
	Matrix4x4 world;
	graphicEngine.setProjectionMatrix(shader, projection);
	
	
	
	graphicEngine.clear();
	
	graphicEngine.setShaderProgram(shader);
	graphicEngine.setTexture(texture);
	uniform->setValue(0);
	graphicEngine.setVertexArrayObject(triangle);
	graphicEngine.setIndexArrayObject(indexes);
	
	
	if(scale > 0.001f)
	{
		//circlesToDraw += 20;
		scale = 0;
	}
	unsigned int index = 0;
	
	float circleSize = 0.003f;
	
	
	world.setIdentity();
	world.setScale(Vector3(1.8f, circleSize, 1));
	float x1 = 0.5f;
	float y1 = 0.05f;
	temp.setIdentity();
	temp.setTranslation(Vector3(
	2 * x1 - 1 + circleSize / 2, 
	2 * y1 - 1 + circleSize / 2,
	0));
	world *= temp;
	graphicEngine.setMatrix(shader, world);
	graphicEngine.drawTriangles(indexes->getSize());
	
	
	world.setIdentity();
	world.setScale(Vector3(circleSize, 1.8f, 1));
	x1 = 0.05f;
	y1 = 0.5f;
	temp.setIdentity();
	temp.setTranslation(Vector3(
	2 * x1 - 1 + circleSize / 2, 
	2 * y1 - 1 + circleSize / 2,
	0));
	world *= temp;
	graphicEngine.setMatrix(shader, world);
	graphicEngine.drawTriangles(indexes->getSize());
	
	
	for(int i = 0; i < numberOfSqueres - 1; i++)
	{
		if(drawLines == 0) {
			break;
		}
		Vector2 a = Vector2(
		x[i + 1] - x[i],
		y[i + 1] - y[i]);
		
		index++;
		world.setIdentity();
		world.setScale(Vector3(a.length() * 2, circleSize, 1));
		
		
		temp.setIdentity();
		temp.setRotationZ( atan(a.y / a.x) );
		world *= temp;


		x1 = (x[i] + x[i + 1]) / 2;
		y1 = (y[i] + y[i + 1]) / 2;
		temp.setIdentity();
		temp.setTranslation(Vector3(
		2 * x1 - 1 + circleSize / 2, 
		2 * y1 - 1 + circleSize / 2,
		0));
		world *= temp;
		
		graphicEngine.setMatrix(shader, world);
		graphicEngine.drawTriangles(indexes->getSize());
		
		if(index == circlesToDraw) {
			break;
		}
	}
	
	index = 0;
	circleSize = 0.01f;
	for(int i = 0; i < numberOfSqueres; i++)
	{
		index++;
		world.setIdentity();
		world.setScale(Vector3(circleSize, circleSize, 1));


		temp.setIdentity();
		temp.setTranslation(Vector3(
		2 * x[i] - 1 + circleSize / 4, 
		2 * y[i] - 1 + circleSize / 4,
		0));
		world *= temp;
		
		graphicEngine.setMatrix(shader, world);
		graphicEngine.drawTriangles(indexes->getSize());
		
		if(index == circlesToDraw) {
			break;
		}
	}
	
	
	
	for(int i = 0; i < 9; i++)
	{
		world.setIdentity();
		world.setScale(Vector3(circleSize, circleSize, 1));


		temp.setIdentity();
		temp.setTranslation(Vector3(
		2 * (0.05f + 0.1f * i) - 1 + circleSize / 2, 
		2 * 0.05f - 1 + circleSize / 2,
		0));
		world *= temp;
		
		graphicEngine.setMatrix(shader, world);
		graphicEngine.drawTriangles(indexes->getSize());
	}

	
	for(int i = 0; i < 9; i++)
	{
		world.setIdentity();
		world.setScale(Vector3(circleSize, circleSize, 1));


		temp.setIdentity();
		temp.setTranslation(Vector3(
		2 * 0.05f - 1 + circleSize / 2, 
		2 * (0.05f + 0.1f * i) - 1 + circleSize / 2,
		0));
		world *= temp;
		
		graphicEngine.setMatrix(shader, world);
		graphicEngine.drawTriangles(indexes->getSize());
	}
	
	
	if (ioSystem.onUpdate()) {
		_running = false;
	}
}

bool App::isRunning()
{
	return _running;
}
