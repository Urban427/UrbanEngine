#include "App.h"
#include <stdio.h>

App::App()
{
}

App::~App()
{
}

void App::onCreate()
{
	graphicEngine.init();
	printf("here");
	
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
