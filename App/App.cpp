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

void App::onCreate()
{
	fulscreen 	= false;
	focus 		= true;
	_running 	= true;
	lockCursor 	= false;
	showCursorParametr 	= true;

	//create input/output system
	IOSystem::onCreate("Sanya lol", 1620 , 720, fulscreen);
	
	//create graphics egine
	GraphicsEngine::init();
	GraphicsEngine::clear(Color(0, 1, 0, 1));
	GraphicsEngine::setCullMode(FrontFace);
	Rect size = IOSystem::getInnerSize();
	setSize(size.width, size.height);
	
	
	//create texture
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
	texture = GraphicsEngine::createTexture({
		(unsigned int)width,
		(unsigned int)height,
		image
	});

	
	
	//create shader
	shader = GraphicsEngine::createShaderProgram({ "./Assets/shader.vsh",  "./Assets/shader.fsh" });
	uniform = GraphicsEngine::createUniformObject({
		shader->getID(),
		"u_TextureUnit",
		0
	});





	//create shape polygons
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
	
	vertexes_indexes = GraphicsEngine::createIndexArrayObject({
		indeces, 
		sizeof(indeces) / sizeof(int)
	});




	//create shape points
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

	Vertex m_vertexes[] = {
		{positionList[0], texcoordsList[1]},
		{positionList[1], texcoordsList[0]},
		{positionList[2], texcoordsList[2]},
		{positionList[3], texcoordsList[3]},
		{positionList[4], texcoordsList[0]},
		{positionList[5], texcoordsList[2]},
		{positionList[6], texcoordsList[3]},
		{positionList[7], texcoordsList[1]}
	};
	

	vertexes = GraphicsEngine::createVertexArrayObject({
		m_vertexes,
		sizeof(Vertex),
		sizeof(m_vertexes) / sizeof(Vertex)
	});
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
	camView.setIdentity();
	camView.setRotationX(rot_y);
	
	temp.setIdentity();
	temp.setRotationY(rot_x);
	camView *= temp;
	
	temp.setIdentity();
	temp.setTranslation(moveTo);
	camView *= temp;
	
	camView.inverse();
}


void App::onUpdate()
{
	if((IOSystem::getInputState()[27] & 0x80) == 0x80 && (IOSystem::getOldInputState()[27] & 0x80) != 0x80)
	{
		showCursorParametr = !showCursorParametr;
		lockCursor = !lockCursor;
		
		IOSystem::showCursor(showCursorParametr);
	}
	if((IOSystem::getInputState()[2] & 0x80) == 0x80 && (IOSystem::getOldInputState()[2] & 0x80) != 0x80)
	{
		fulscreen = !fulscreen;
		IOSystem::setFullscreen(fulscreen);
	}
	
	if((getInputState()[46] & 0x80) == 0x80 && (getOldInputState()[46] & 0x80) != 0x80)
	{
		setVSync(!getVSync());
	}
	
	Vector2 cursor(0, 0);
	if((IOSystem::getInputState()[1] & 0x80) == 0x80 || (lockCursor && focus))
	{
		cursor = IOSystem::deltaCursorPos();
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
	GraphicsEngine::setProjectionMatrix(shader, projection);
	calculateCameraView();

	//set material
	GraphicsEngine::setShaderProgram(shader);
	GraphicsEngine::setTexture(texture);
	//uniform->setValue(texture->getID());
	
	//set shape
	GraphicsEngine::setVertexArrayObject(vertexes);
	GraphicsEngine::setIndexArrayObject(vertexes_indexes);
	
	
	
	//calculate object projection
	Matrix4x4 world, temp;
	world.setIdentity();
	world.setScale(Vector3(2, 1, 1));
	
	temp.setIdentity();
	temp.setRotationY(45 * 3.14f / 180.0f);
	world *= temp;
	
	temp.setIdentity();
	temp.setTranslation(Vector3(0, 0, -3));
	world *= temp;
	
	world *= camView;
	
	
	
	//draw object 
	GraphicsEngine::setMatrix(shader, world);
	GraphicsEngine::drawTriangles(vertexes_indexes->getSize());


	//update ioSystem{
	IOSystem::onUpdate();
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
	0.01f, 111);
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
{
	focus = false;
	IOSystem::showCursor(true);
}