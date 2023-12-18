#include "App.h"
#include "Color.h"
#include "Matrix4x4.h"
#include "FileManager.h"
#include "Rect.h"

#include <math.h>
#include <cmath>
#include <malloc.h>

App::App()
{
}

//App::~App(){}

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
	graphicEngine.setViewPort(ioSystem.getInnerSize());
	graphicEngine.clear(Color(0, 0, 1, 1));
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
	
	
	shader = graphicEngine.createShaderProgram({ "./Assets/shader.vsh",  "./Assets/shader.fsh" });
	
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
	
	ioSystem.showCursor(showCursor);
	ioSystem.createInputState();
	inputState =  ioSystem.getInputState();
	oldinputState =  ioSystem.getOldInputState();
	ioSystem.moveCursor();
}

void  App::setSize(unsigned int width, unsigned int height)
{
	ioSystem.setSize(width, height);
}

void App::setInput(float x, float y)
{
	
}

void  App::Move()
{
	moveTo.x += 0.03f;
}
	
void App::onUpdate()
{
	graphicEngine.setViewPort(ioSystem.getInnerSize());
	Vector2 cursor(0, 0);
	if(showCursor == false)
	{
		cursor = ioSystem.moveCursor();
	}
	rot_x += cursor.x * 0.003f;
	rot_y += cursor.y * 0.003f;
	ioSystem.updateInputState();
	float speed = 3;
	if(inputState[87]  >> 7 == 1)
	{
		x = -0.003f * speed;
	}
	else if(inputState[83] >> 7 == 1)
	{
		x = 0.003f * speed;
	}
	else
	{
		x = 0;
	}
	
	if(inputState[65] >> 7 == 1)
	{
		y = -0.003f * speed;
	}
	else if(inputState[68] >> 7 == 1)
	{
		y = 0.003f * speed;
	}
	else
	{
		y = 0;
	}
	
	if(inputState[32] >> 7 == 1)
	{
		up = 0.003f * speed;
	}
	else if(inputState[17] >> 7 == 1)
	{
		up = -0.003f * speed;
	}
	else
	{
		up = 0;
	}
	
	if((inputState[27] & 0x80) == 0x80 && (inputState[27] & 0x80) != (oldinputState[27] & 0x80))
	{
		showCursor = !showCursor;
		ioSystem.showCursor(showCursor);
		Rect rc = ioSystem.getCenter();
		ioSystem.setInput(rc.width, rc.height);
	}
	
	
	Matrix4x4 temp, camView;
	
	camView.setIdentity();
	camView.setRotationX(rot_y);
	
	temp.setIdentity();
	temp.setRotationY(rot_x);
	camView *= temp;
	
	moveTo += camView.getZDirection().normalized() * x;
	moveTo += camView.getXDirection().normalized() * y;
	moveTo += camView.getYDirection().normalized() * up;
	temp.setIdentity();
	temp.setTranslation(moveTo);
	camView *= temp;
	
	camView.inverse();
	
	
	
	
	graphicEngine.clear();
	
	graphicEngine.setShaderProgram(shader);
	graphicEngine.setTexture(texture);
	uniform->setValue(0);
	graphicEngine.setVertexArrayObject(triangle);
	graphicEngine.setIndexArrayObject(indexes);
	
	
	
	Rect size = ioSystem.getInnerSize();
	Matrix4x4 projection;
	projection.setIdentity();
	//projection.setOrthoLH(size.width * 0.004f, size.height * 0.004f, -4, 4);
	projection.setPerspectiveFovLH(
	1.17f, 
	(float)size.width / (float)size.height,
	0.01f, 111);
	graphicEngine.setProjectionMatrix(shader, projection);
	
	
	
	
	Matrix4x4 world;
	world.setIdentity();
	world.setScale(Vector3(1, 1, 1));


	temp.setIdentity();
	temp.setTranslation(Vector3(
	0, 
	0,
	-3));
	world *= temp;
	world *= camView;
	
	graphicEngine.setMatrix(shader, world);
	graphicEngine.drawTriangles(indexes->getSize());


	
	if (ioSystem.onUpdate()) {
		_running = false;
	}
}

bool App::isRunning()
{
	return _running;
}
