#include "GraphicsEngine.h"
#include "glad/glad.h"

GraphicsEngine::GraphicsEngine()
{

}

bool GraphicsEngine::init()
{
	gladLoadGL();
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

void GraphicsEngine::setVertexArrayObject(const VertexArrayObjectPtr& vao)
{
	glBindVertexArray(vao->getID());
	
}

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& desc)
{
	return std::make_shared<VertexArrayObject>(desc);
}

void GraphicsEngine::drawTriangles(unsigned int vertexCount, unsigned int offset)
{
	glDrawArrays(GL_TRIANGLES, offset, vertexCount);
}

ShaderPtr GraphicsEngine::createShaderProgram(const ShaderDesc& desc)
{
	return std::make_shared<Shader>(desc);
}

void GraphicsEngine::setShaderProgram(const ShaderPtr& program)
{
	glUseProgram(program->getID());
}