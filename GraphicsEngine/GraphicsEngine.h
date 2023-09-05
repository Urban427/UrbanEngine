#pragma once
#include "Rect.h"
#include "Color.h"

class GraphicsEngine
{
public:
	GraphicsEngine();

	bool init();
	bool update();
	bool release();
	
	void clear(const Color& color);
	void setViewPort(const Rect& size);

	~GraphicsEngine();
};

