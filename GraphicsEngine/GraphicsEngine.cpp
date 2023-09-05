#include "GraphicsEngine.h"
#include <gl/gl.h>

GraphicsEngine::GraphicsEngine()
{

}

bool GraphicsEngine::init()
{
	clear(Color(1, 0, 1, 1));
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

bool GraphicsEngine::update()
{
	setViewPort(Rect(0, 0, 120, 120));
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	glPushMatrix();
	glRotatef(theta, 0.0f, 0.0f, 1.0f);
	
	glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.87f, -0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.87f, -0.5f);

	glEnd();
	
	glPopMatrix();

	theta += 1.0f;
	
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

void GraphicsEngine::setVertexArrayObject(const VertexArrayObjectPtr& vao)
{
	
}

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferData& data)
{
	return std::make_shared<VertexArrayObject>(data);
}