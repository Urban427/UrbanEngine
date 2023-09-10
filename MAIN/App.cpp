#include "App.h"

App::App()
{
}

App::~App()
{
}

void App::onCreate()
{
	_running = true;
	if (ioSystem.onCreate()) {
		_running = false;
	}
	
	graphicEngine.init();
	//graphicEngine.setViewPort(ioSystem.getInnerSize());
	graphicEngine.clear(Color(1, 0, 0, 1));
	
	
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

void App::onUpdate()
{
	graphicEngine.clear();
	
	
	graphicEngine.setShaderProgram(shader);
	graphicEngine.setVertexArrayObject(triangle);
	graphicEngine.drawTriangles(triangle->getVertexBufferSize(), 0);
	
	
	if (ioSystem.onUpdate()) {
		_running = false;
	}
}

bool App::isRunning()
{
	return _running;
}
