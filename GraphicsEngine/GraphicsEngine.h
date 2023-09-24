#pragma once
#include "Rect.h"
#include "Matrix4x4.h"
#include "Color.h"
#include "VertexArrayObject.h"
#include "IndexArrayObject.h"
#include "UniformObject.h"
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

	bool init();
	~GraphicsEngine();
	
public:
	void clear();
	void clear(const Color& color);
	void setViewPort(const Rect& size);
	void setIndexArrayObject(IndexArrayObject* iao);
	void setVertexArrayObject(VertexArrayObject* vao);
	void setShaderProgram(Shader* program);
	void setTexture(Texture* texture);
	
	void setMatrix(Shader* shader, Matrix4x4& matrix);
	void setProjectionMatrix(Shader* shader, Matrix4x4& matrix);
	void drawTriangles(unsigned int vertexCount);
	
	void setCullMode(const CullMode& mode);
public:
	UniformObject* createUniformObject(const UniformDesc& desc); 
	VertexArrayObject* createVertexArrayObject(const VertexBufferDesc& desc); 
	IndexArrayObject* createIndexArrayObject(const IndexArrayDesc& desc);
	Shader* createShaderProgram(const ShaderDesc& desc);
	Texture* createTexture(const TextureDesc& desc);
};

