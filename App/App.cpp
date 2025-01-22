#include "App.h"
#include "Color.h"
#include "Matrix4x4.h"
#include "Rect.h"
#include "KeyCodes.h"

#include <math.h>
#include <cmath>
#include <malloc.h>
#include <stdio.h>
#include <chrono>

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
	
	
	physicHouse = IOSystem::readFBX("testMesh.fbx");
	vertexes_indexes2 = GraphicsEngine::createIndexArrayObject({ (unsigned int*)physicHouse.index,  (unsigned int)physicHouse.index_size });
	vertexes2 = GraphicsEngine::createVertexArrayObject({ physicHouse.vertex, sizeof(Vertex), (unsigned int)physicHouse.vertex_size });
	
	player.transform->position 	= Vector3(5, 5, 5);
	player.transform->rotation  = Quaternion(0, -0.33f, 0, 1);
	player.camera->rotation 	=  Quaternion(0, sin(45 * 0.5f * (M_PI / 180)), 0, cos(45 * 0.5f * (M_PI / 180.0f))); 
	player.camera->rotation.normalize();
	for(unsigned int i = 0; i <  number_of_objects; i++)
	{
		collisions[i].offset = Vector3(static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand())).normalized() * 0.1f;
		collisions[i].radius = static_cast<float>(rand() % 1000) / 20000 + 0.01;
		transform[i].scale = Vector3(collisions[i].radius, collisions[i].radius, collisions[i].radius);
		aabb[i] = {Vector3(-collisions[i].radius, -collisions[i].radius, -collisions[i].radius), Vector3(collisions[i].radius, collisions[i].radius, collisions[i].radius), i};
		collisions[i].radius /= 2;
	}
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
	//temp.setRotation(player.transform->rotation);
	
	cam.setIdentity();
	cam.setRotation(player.camera->rotation);
	//printf("%f %f %f %f\n", player.camera->rotation.x, player.camera->rotation.y, player.camera->rotation.z, player.camera->rotation.w);
	//cam *= temp;
	
	temp.setIdentity();
	temp.setTranslation(Vector3(3, 0, 3));
	cam *= temp;
	
	camView = cam;
	camView.inverse();
}


void App::onUpdate()
{
	 auto start = std::chrono::high_resolution_clock::now();
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
	simulatePhysic(transform, collisions, aabb, number_of_objects, transform_static, static_meshes, 1);

	
	if(lockCursor && focus) {
		IOSystem::setCenterCursorPos();
	}
	
	//clear render target
	GraphicsEngine::clear();
	
	//set material
	GraphicsEngine::setShaderProgram(shader);
	GraphicsEngine::setTexture(texture[0], shader);
	
	
	//calculate new camera projections
	calculateCameraView();
	GraphicsEngine::setProjectionMatrix(shader, projection);
	GraphicsEngine::setCameraViewMatrix(shader, camView);
	
	
	
	
	
	//set shape
	GraphicsEngine::setVertexArrayObject(vertexes);
	GraphicsEngine::setIndexArrayObject(vertexes_indexes);
	
	
	//draw object 
	for(int i = 1; i < number_of_objects; i++) {
		Matrix4x4 world, temp;
		world.setIdentity();
		world.setScale(transform[i].scale);
		
		temp.setIdentity();
		temp.setTranslation(transform[i].position);
		world *= temp;
		
		GraphicsEngine::setMatrix(shader, world);
		GraphicsEngine::drawTriangles(vertexes_indexes->getNumberOfMaterials(), 0);
	}
	
	Matrix4x4 world1;
	world1.setIdentity();
	world1.setRotationY(t);		
	
	GraphicsEngine::setMatrix(shader, world1);
	GraphicsEngine::setVertexArrayObject(vertexes2);
	GraphicsEngine::setIndexArrayObject(vertexes_indexes2);
	GraphicsEngine::drawTriangles(vertexes_indexes2->getNumberOfMaterials(), 0);

	

	//update ioSystem
	IOSystem::onUpdate();
	
	auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Output the duration in milliseconds
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

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