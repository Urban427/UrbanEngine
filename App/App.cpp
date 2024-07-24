#include "App.h"
#include "Color.h"
#include "Matrix4x4.h"
#include "Rect.h"
#include "KeyCodes.h"
#include "Physic.h"

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
	initKeyCodes(IOSystem::getInputState(), IOSystem::getOldInputState(), IOSystem::getPos(), IOSystem::getOldPos());
	
	//create graphics egine
	GraphicInit();
	
	
	//create texture
	texture[0] = GraphicsEngine::createTexture(IOSystem::readBMP("ghost2.bmp"));

	
	//create shader
	shader = GraphicsEngine::createShaderProgram({openCFile("shader.vsh").getPtr(), openCFile("shader.fsh").getPtr()});

	
	//create shape points
	Mesh mesh = IOSystem::readFBX("sphere.fbx");
	vertexes_indexes = GraphicsEngine::createIndexArrayObject({ (unsigned int*)mesh.index,  (unsigned int)mesh.index_size });
	vertexes = GraphicsEngine::createVertexArrayObject({ mesh.vertex, sizeof(Vertex), (unsigned int)mesh.vertex_size });
	//freeMesh(mesh);
	
	player.transform->position 	= Vector3(5, 5, 5);
	player.camera->rotation 	= Quaternion(0, 0.33f, 0, 1) * Quaternion(-0.3f, 0, 0, 1);
}

void App::setInput(float x, float y)
{
	
}

void  App::Move()
{
	player.transform->position.z -= 0.1f;
}



void App::calculateCameraView()
{
	Matrix4x4 temp;
	temp.setRotation(player.transform->rotation);
	
	cam.setIdentity();
	cam.setRotation(player.camera->rotation);
	cam *= temp;
	
	temp.setIdentity();
	temp.setTranslation(player.transform->position);
	cam *= temp;
	
	camView = cam;
	camView.inverse();
}


void App::onUpdate()
{
	//gamelogic
	t+=0.01f;
	
	if(GetKeyDown(KeyCode_Escape)) {
		showCursorParametr = !showCursorParametr;
		lockCursor = !lockCursor;
		IOSystem::showCursor(showCursorParametr);
	}
	
	if(GetKeyDown(KeyCode_RightMouseButton)) {
		fulscreen = !fulscreen;
		IOSystem::setFullscreen(fulscreen);
	}
	
	if(GetKeyDown(KeyCode_Delete)) {
		setVSync(!getVSync());
	}
	
	UpdateFPSO(&player, 1);
	calculatePhysic(transform, number_of_objects);
	
	if(lockCursor && focus) {
		IOSystem::setCenterCursorPos();
	}
	
	//clear render target
	GraphicsEngine::clear();
	
	//calculate new camera projections
	calculateCameraView();
	GraphicsEngine::setProjectionMatrix(shader, projection);
	GraphicsEngine::setCameraViewMatrix(shader, camView);
	
	
	
	
	
	//set shape
	GraphicsEngine::setVertexArrayObject(vertexes);
	GraphicsEngine::setIndexArrayObject(vertexes_indexes);
	
	
	//set material
	GraphicsEngine::setShaderProgram(shader);
	GraphicsEngine::setTexture(texture[0], shader);
	
	//draw object 
	for(int i = 1; i < number_of_objects; i++)
	{
		//calculate object projection
		Matrix4x4 world, temp;
		world.setIdentity();
		world.setScale(Vector3(0.1f, 0.1f, 0.1f));
		temp.setIdentity();
		//temp.setRotation(transform->rotation);
		world *= temp;
		temp.setIdentity();
		temp.setTranslation(transform[i].position);
		world *= temp;
		//printf("%f %f %f\n", transform[i].position.x, transform[i].position.y, transform[i].position.z);

		GraphicsEngine::setMatrix(shader, world);
		GraphicsEngine::drawTriangles(vertexes_indexes->getNumberOfMaterials(), 0);
	}


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