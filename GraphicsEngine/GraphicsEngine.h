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
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
	void setShaderProgram(const ShaderPtr& program);
	void drawTriangles(unsigned int vertexCount, unsigned int offset);
public:
	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& desc);
	ShaderPtr createShaderProgram(const ShaderDesc& desc);
	
	unsigned int texture_object_id;
};

