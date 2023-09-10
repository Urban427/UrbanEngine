#pragma once
#include "Rect.h"
#include "Color.h"
#include "VertexArrayObject.h"
#include "Shader.h"


class GraphicsEngine
{
public:
	GraphicsEngine();

	bool init();
	~GraphicsEngine();
	
public:
	void clear();
	void clear(const Color& color);
	void setViewPort(const Rect& size);
	void setVertexArrayObject( VertexArrayObject* vao);
	void setShaderProgram( Shader* program);
	void drawTriangles(unsigned int vertexCount, unsigned int offset);
public:
	VertexArrayObject* createVertexArrayObject(const VertexBufferDesc& desc); 
	Shader* createShaderProgram(const ShaderDesc& desc);
};

