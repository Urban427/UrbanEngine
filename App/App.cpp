#include "App.h"
#include "Color.h"
#include "Matrix4x4.h"
#include "Rect.h"
#include "KeyCodes.h"

#include <math.h>
#include <cmath>
#include <malloc.h>
#include <stdio.h>

unsigned int r = 24;

void App::GraphicInit()
{
	GraphicsEngine::init();
	GraphicsEngine::clear(Color(0, 0, 0, 1));
	GraphicsEngine::setCullMode(BackFace);
	Rect size = IOSystem::getInnerSize();
	setSize(size.width, size.height);
}

void App::onCreate()
{
	fulscreen 	= false;
	focus 		= true;
	_running 	= true;
	lockCursor 	= false;
	showCursorParametr 	= true;

	//create input/output system
	IOSystem::onCreate("Sanya lol", 500 , 200, fulscreen);
	
	//create graphics egine
	GraphicInit();
	
	
	//create texture
	char* textureData = IOSystem::readFile("0012.b").start;
	unsigned int width =  (unsigned int)(*textureData);
	unsigned int height = (unsigned int)(textureData[4]);
	unsigned int* image = (unsigned int*)(textureData + 8);
	texture[0] = GraphicsEngine::createTexture({width, height, image});

	
	//create shader
	shader = GraphicsEngine::createShaderProgram({IOSystem::readFile("shader.vsh").start, IOSystem::readFile("shader.fsh").start});
	uniform = GraphicsEngine::createUniformObject({shader->getID(), "u_TextureUnit", 0});

	
	//create shape points
	char buffer[64];
	Mesh mesh = IOSystem::readFBX("cube.fbx");
	vertexes_indexes = GraphicsEngine::createIndexArrayObject({ (unsigned int*)mesh.index,  (unsigned int)mesh.index_size });
	vertexes = GraphicsEngine::createVertexArrayObject({ mesh.vertex, sizeof(Vector3) + sizeof(Vector2) + sizeof(Vector3), (unsigned int)mesh.vertex_size });
}

void App::setInput(float x, float y)
{
	
}

void  App::Move()
{
	moveTo.x += 0.03f;
}



void App::calculateCameraView()
{
	Matrix4x4 temp;
	cam.setIdentity();
	cam.setRotationX(rot_y);
	
	temp.setIdentity();
	temp.setRotationY(rot_x);
	cam *= temp;
	
	temp.setIdentity();
	temp.setTranslation(moveTo);
	cam *= temp;
	
	camView = cam;
	camView.inverse();
}


void App::onUpdate()
{
	t+=0.01f;
	//gamelogic
	if((IOSystem::getInputState()[27] & 0x80) == 0x80 && (IOSystem::getOldInputState()[27] & 0x80) != 0x80) //ESC
	{
		showCursorParametr = !showCursorParametr;
		lockCursor = !lockCursor;
		
		IOSystem::showCursor(showCursorParametr);
	}
	if((IOSystem::getInputState()[2] & 0x80) == 0x80 && (IOSystem::getOldInputState()[2] & 0x80) != 0x80) //Left Mouse Button
	{
		fulscreen = !fulscreen;
		IOSystem::setFullscreen(fulscreen);
	}
	
	if((getInputState()[46] & 0x80) == 0x80 && (getOldInputState()[46] & 0x80) != 0x80) //DELETE button
	{
		setVSync(!getVSync());
	}
	
	Vector2 cursor(0, 0);
	if((IOSystem::getInputState()[1] & 0x80) == 0x80 || (lockCursor && focus)) //Right Mouse Button
	{
		cursor = IOSystem::deltaCursorPos();
	}
	
	if((IOSystem::getInputState()[65] & 0x80) == 0x80) //A
	{
		calculateCameraView();
		moveTo -= cam.getXDirection() * 0.1f;
	}
	else if((IOSystem::getInputState()[68] & 0x80) == 0x80) //D
	{
		calculateCameraView();
		moveTo += cam.getXDirection() * 0.1f;
	}
	if((IOSystem::getInputState()[87] & 0x80) == 0x80) //W
	{
		calculateCameraView();
		moveTo -= cam.getZDirection() * 0.1f;
	}
	else if((IOSystem::getInputState()[83] & 0x80) == 0x80) //S
	{
		calculateCameraView();
		moveTo += cam.getZDirection() * 0.1f;
	}
	
	
	rot_x += cursor.x * 0.003f;
	rot_y -= cursor.y * 0.003f;
	if(lockCursor && focus)
	{
		IOSystem::setCenterCursorPos();
	}
	
	//clear render target
	GraphicsEngine::clear();
	
	//calculate new camera projections
	calculateCameraView();
	GraphicsEngine::setProjectionMatrix(shader, projection);
	GraphicsEngine::setCameraViewMatrix(shader, camView);
	
	//set material
	GraphicsEngine::setShaderProgram(shader);
	GraphicsEngine::setTexture(texture[0]);
	//uniform->setValue(texture->getID());
	
	//calculate object projection
	Matrix4x4 world, temp;
	world.setIdentity();
	world.setScale(Vector3(0.3f, 0.3f, 0.3f));
	temp.setIdentity();
	temp.setRotationY(t);
	world *= temp;
	temp.setIdentity();
	temp.setTranslation(Vector3(0, 0, -3));
	world *= temp;
	
	
	//set shape
	GraphicsEngine::setVertexArrayObject(vertexes);
	GraphicsEngine::setIndexArrayObject(vertexes_indexes);
	
	//draw object 
	GraphicsEngine::setMatrix(shader, world);
	GraphicsEngine::drawTriangles(36, 0);


	//update ioSystem{
	IOSystem::onUpdate();
}


void App::render()
{
	
}


bool App::isRunning()
{
	return _running;
}






void App::setSize(unsigned int width, unsigned int height)
{
	IOSystem::setSize(width, height);
	if(GraphicsEngine::inizilizated){
		GraphicsEngine::setViewPort(width, height);
	}
	
	projection.setIdentity();
	//projection.setOrthoLH(width * 0.004f, height * 0.004f, -4, 4);
	projection.setPerspectiveFovLH(
	1.17f, 
	(float)width / (float)height,
	0.01f, 1111);
}

void App::onDestroy()
{
	_running = false;
}

void App::onFocus()
{
	focus = true;
	if(lockCursor)
	{
		IOSystem::setCursorPosWithoutMoving();
	}
	IOSystem::showCursor(showCursorParametr);
}

void App::onKillFocus()
{focus = false;
	IOSystem::showCursor(true);
}