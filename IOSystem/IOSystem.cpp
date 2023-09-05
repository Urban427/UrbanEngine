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


Rect IOSystem::getInnerSize()
{
	return _window.getInnerSize();
}