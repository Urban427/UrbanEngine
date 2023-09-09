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

	bool isRunning();
private:
	VertexArrayObjectPtr triangle;
	ShaderPtr shader;

	bool _running = false;
	IOSystem ioSystem;
	GraphicsEngine graphicEngine;
};

