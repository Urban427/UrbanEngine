#pragma once
#include "Rect.h"
#include "Matrix4x4.h"
#include "Color.h"
#include "VertexArrayObject.h"
#include "IndexArrayObject.h"
#include "Shader.h"
#include "Texture.h"

enum CullMode
{
	BackFace = 0,
	FrontFace,
	Both
};

class GraphicsEngine
{
public:
	GraphicsEngine();
	//~GraphicsEngine();
	bool init();
	
public:
	bool inizilizated = false;
public:
	void clear();
	void clear(const Color& color);
	void setViewPort(const unsigned int& width, const unsigned int& height);
	void setIndexArrayObject(IndexArrayObject* iao);
	void setVertexArrayObject(VertexArrayObject* vao);
	void setShaderProgram(Shader* program);
	void setTexture(Texture* texture, Shader* shader);
	
	void setMatrix(Shader* shader, Matrix4x4& matrix);
	void setProjectionMatrix(Shader* shader, Matrix4x4& matrix);
	void setCameraViewMatrix(Shader* shader, Matrix4x4& matrix);
	void drawTriangles(unsigned int vertexCount, void* offset);
	
	void setCullMode(const CullMode& mode);
public:
	VertexArrayObject* createVertexArrayObject(const VertexBufferDesc& desc); 
	IndexArrayObject* createIndexArrayObject(const IndexArrayDesc& desc);
	Shader* createShaderProgram(const ShaderDesc& desc);
	Texture* createTexture(const TextureStruct desc);
};

