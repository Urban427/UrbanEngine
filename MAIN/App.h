#pragma once
#include "IOSystem.h"
#include "GraphicsEngine.h"

class App
{
public:
	App();
	~App();

	void onCreate();
	void onUpdate();

	void setSize(unsigned int width, unsigned int height);

	bool isRunning();
private:
	VertexArrayObject* triangle;
	Shader* shader;
	IndexArrayObject* indexes;
	UniformObject* uniform;
	Texture* texture;

	float scale = 0;

	bool _running = false;
	IOSystem ioSystem;
	GraphicsEngine graphicEngine;
	
	
	char drawLines = 1;
	unsigned int circlesToDraw = 1;
	float numberOfSqueres = 3333;
	float* x;
	float* y;
	
};

