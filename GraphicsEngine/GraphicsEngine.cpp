#include "GraphicsEngine.h"
#include <malloc.h>

#ifdef glad
	#include "glad/glad.h"
#elif gles2
	#include "gles2/gl2.h"
#endif


GraphicsEngine::GraphicsEngine() { }
//GraphicsEngine::~GraphicsEngine() { }


bool GraphicsEngine::init()
{
#ifdef glad
	gladLoadGL();
#endif
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glDepthRangef(0.0f, 1.0f);

	inizilizated = true;
	return true;
}



void GraphicsEngine::clear(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void GraphicsEngine::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
}

void GraphicsEngine::setViewPort(const unsigned int& width, const unsigned int& height)
{
	glViewport(0, 0, width, height);
}

void GraphicsEngine::drawTriangles(unsigned int vertexCount)
{
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount);
	glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
}


void GraphicsEngine::setVertexArrayObject(VertexArrayObject* vao)
{
#ifdef glad
	glBindVertexArray(vao->getID());
#elif gles2
	glBindBuffer(GL_ARRAY_BUFFER, vao->getID());
#endif
}


void GraphicsEngine::setIndexArrayObject(IndexArrayObject* iao)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iao->getID());
}

void GraphicsEngine::setShaderProgram(Shader* program)
{
	glUseProgram(program->getID());
}

void GraphicsEngine::setTexture(Texture* texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getID()); 
}

void GraphicsEngine::setMatrix(Shader* shader, Matrix4x4& matrix)
{
	unsigned int transformLoc = glGetUniformLocation(shader->getID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, matrix.getPtr());
}

void GraphicsEngine::setProjectionMatrix(Shader* shader, Matrix4x4& matrix)
{
	unsigned int transformLoc = glGetUniformLocation(shader->getID(), "projection");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, matrix.getPtr());
}


void GraphicsEngine::setCullMode(const CullMode& mode)
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	switch(mode)
	{
		case(BackFace):
		{
			glCullFace(GL_BACK);
			break;
		}
		case(FrontFace):
		{
			glCullFace(GL_FRONT);
			break;
		}
		case(Both):
		{
			glCullFace(GL_FRONT_AND_BACK);
			break;
		}
	}
}



UniformObject* GraphicsEngine::createUniformObject(const UniformDesc& desc)
{
	UniformObject* m = (UniformObject*)malloc(sizeof(UniformObject));
	m->init(desc);
	return m;
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

IndexArrayObject* GraphicsEngine::createIndexArrayObject(const IndexArrayDesc& desc)
{
	IndexArrayObject* m = (IndexArrayObject*)malloc(sizeof(IndexArrayObject));
	m->init(desc);
	return m;
}

Texture* GraphicsEngine::createTexture(const TextureDesc& desc)
{
	Texture* m = (Texture*)malloc(sizeof(Texture));
	m->init(desc);
	return m;
}