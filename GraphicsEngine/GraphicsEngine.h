#pragma once
#include "Rect.h"
#include "Color.h"
#include "VertexArrayObject.h"

class GraphicsEngine
{
public:
	GraphicsEngine();

	bool init();
	bool update();
	bool release();
	~GraphicsEngine();
	
public:
	void clear(const Color& color);
	void setViewPort(const Rect& size);
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
public:
	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferData& data);
	
	
	float theta = 0;
};

