#include "IOSystem.h"

IOSystem::IOSystem()
{

}

IOSystem::~IOSystem()
{

}

char IOSystem::onCreate()
{
    return _window.init();
}

char IOSystem::onUpdate()
{
    return _window.broadcast();
}



double IOSystem::getTime()
{
	return _window.getTime();
}



void IOSystem::setSize(unsigned int width, unsigned int height)
{
	_window.setSize(width, height);
}

Rect IOSystem::getInnerSize()
{
	return _window.getInnerSize();
}



void IOSystem::createInputState()
{
	
}

void IOSystem::updateInputState()
{
	
}
