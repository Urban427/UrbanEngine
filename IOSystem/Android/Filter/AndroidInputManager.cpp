#include "AndroidInputManager.h"


AndroidInputManager:: AndroidInputManager() {}
//AndroidInputManager::~AndroidInputManager() {}

void AndroidInputManager::create(WindowInputs& windowInput)
{
	
}

void AndroidInputManager::update() 
{
	
}

unsigned char* AndroidInputManager::getState()
{
	return keys;
}

unsigned char* AndroidInputManager::getOldState()
{
	return oldKeys;
}

Vector2 AndroidInputManager::getCursorPos()
{
	return Vector2(0, 0);
}


void AndroidInputManager::showCursor(bool state)
{
	
}

void  AndroidInputManager::setCursorPos(int x, int y)
{
	
}

Vector2 AndroidInputManager::moveCursorFrame(int x, int y) 
{
	return Vector2(0, 0);
}