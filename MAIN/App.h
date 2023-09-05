#pragma once
#include "IOSystem.h"
#include "../GraphicsEngine/GraphicsEngine.h"

class App
{
public:
	App();
	~App();

	void onCreate();
	void onUpdate();

	bool isRunning();
private:
	bool _running = false;
	IOSystem ioSystem;
	GraphicsEngine graphicEngine;
};

