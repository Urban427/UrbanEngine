#include "App.h"
#include "GraphicsEngine.h"
#include "IOS

App::App()
{
}

App::~App()
{
}

void App::onCreate()
{
	_running = true;
	if (ioSystem.onCreate())
	{
		_running = false;
	}
}

void App::onUpdate()
{
	if (ioSystem.onUpdate())
	{
		_running = false;
	}
}

bool App::isRunning()
{
	return _running;
}
