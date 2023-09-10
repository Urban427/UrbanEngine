#include "GraphicsEngine.h"
#include <malloc.h>

#ifdef glad
	#include "glad/glad.h"
#elif gles2
	#include "gles2/gl2.h"
#endif


GraphicsEngine::GraphicsEngine()
{

}

bool GraphicsEngine::init()
{
#ifdef glad
	gladLoadGL();
#endif
	return true;
}

GraphicsEngine::~GraphicsEngine()
{
	
}



void GraphicsEngine::clear(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void GraphicsEngine::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::setViewPort(const Rect& size)
{
	glViewport(size.left, size.top, size.width, size.height);
}

void GraphicsEngine::drawTriangles(unsigned int vertexCount, unsigned int offset)
{
	glDrawArrays(GL_TRIANGLE_STRIP, offset, vertexCount);
}

void GraphicsEngine::setVertexArrayObject(VertexArrayObject* vao)
{
#ifdef glad
	glBindVertexArray(vao->getID());
#elif gles2
	glBindBuffer(GL_ARRAY_BUFFER, vao->getID());
#endif
}

void GraphicsEngine::setShaderProgram(Shader* program)
{
	glUseProgram(program->getID());
}

VertexArrayObject* GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& desc)
{
	VertexArrayObject* m = (VertexArrayObject*)malloc(sizeof(VertexArrayObject));
	m->init(desc);
	return m;
}

Shader* GraphicsEngine::createShaderProgram(const ShaderDesc& desc)
{
	Shader* m = (Shader*)malloc(sizeof(Shader));
	m->init(desc);
	return m;
}