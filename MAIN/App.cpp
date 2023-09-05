#include "App.h"

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
	
	graphicEngine.init();
}

void App::onUpdate()
{
	graphicEngine.update();
	if (ioSystem.onUpdate())
	{
		_running = false;
	}
}

bool App::isRunning()
{
	return _running;
}
