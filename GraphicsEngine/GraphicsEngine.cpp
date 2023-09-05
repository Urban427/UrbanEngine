#include "GraphicsEngine.h"
#include <gl/gl.h>

GraphicsEngine::GraphicsEngine()
{

}

bool GraphicsEngine::init()
{
	setViewPort(Rect(0, 0, 120, 120));
	clear(Color(1, 0, 1, 1));
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

bool GraphicsEngine::update()
{
	setViewPort(Rect(0, 0, 120, 120));
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}


bool GraphicsEngine::release()
{
	return false;
}

GraphicsEngine::~GraphicsEngine()
{
}



void GraphicsEngine::clear(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void GraphicsEngine::setViewPort(const Rect& size)
{
	glViewport(size.left, size.top, size.width, size.height);
}