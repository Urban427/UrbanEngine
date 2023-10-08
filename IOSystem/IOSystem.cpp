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



void IOSystem::initTime()
{
	_window.initTime();
}

double IOSystem::getDeltaTime()
{
	return _window.getDeltaTime();
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
