#include "App.h"

App::App()
{
}

App::~App()
{
}

void App::onCreate()
{
	const float triangleVertecles[] = {
		-0.5f, -0.5f, 0,
		 0.5f, -0.5f, 0,
		 0, 0.5f, 0
	};
	
	
	_running = true;
	if (ioSystem.onCreate())
	{
		_running = false;
	}
	
	graphicEngine.init();
	graphicEngine.setViewPort(ioSystem.getInnerSize());
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
