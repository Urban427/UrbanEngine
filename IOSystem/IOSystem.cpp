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

Rect IOSystem::getCenter()
{
	return _window.getCenter();
}



void IOSystem::createInputState()
{
	_input.create(windowInputs);
}

void IOSystem::updateInputState()
{
	_input.update();
}

void  IOSystem::setInput(float x, float y)
{
	_input.setCursorPos(x, y);
}

unsigned char* IOSystem::getInputState()
{
	return _input.getState();
}

unsigned char* IOSystem::getOldInputState()
{
	return _input.getOldState();
}

void IOSystem::showCursor(bool state)
{
	_input.showCursor(state);
}

Vector2 IOSystem::moveCursor()
{
	Rect rect = _window.getCenter();
	return _input.moveCursorFrame(rect.width, rect.height);
}