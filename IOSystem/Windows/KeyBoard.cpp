#include "KeyBoard.h"
#include <Windows.h>


keyBoard::keyBoard()
{
	
}

keyBoard::~keyBoard()
{
	
}

void keyBoard::create(WindowInputs& windowInput)
{
	windowInput.number = 1;
	windowInput.states = new unsigned char(0);
	windowInput.poses  = new Vector2(0, 0);
	
	
	if(GetKeyboardState(keyBoarState) == 0) { }
	
	unsigned char* ptrA = keyBoarState;
	unsigned char* ptrB = oldkeyBoarState;
	for(unsigned int i = 0; i < 256; i++)
	{
		(*ptrB) = (*ptrA);
		ptrA++;
		ptrB++;
	}
}

void keyBoard::update()
{
	//(*ptr) = (*ptr) >> 7;
	unsigned char* ptrA = keyBoarState;
	unsigned char* ptrB = oldkeyBoarState;
	for(unsigned int i = 0; i < 256; i++)
	{
		(*ptrB) = (*ptrA);
		ptrA++;
		ptrB++;
	}
	if(GetKeyboardState(keyBoarState) == 0) { }
}


unsigned char* keyBoard::getState()
{
	return keyBoarState;
}

unsigned char* keyBoard::getOldState()
{
	return oldkeyBoarState;
}


Vector2 keyBoard::getCursorPos()
{
	POINT p;
	GetCursorPos(&p);
	return Vector2(p.x, p.y);
}

void keyBoard::setCursorPos(int x, int y)
{
	SetCursorPos(x, y);
}


void keyBoard::showCursor(bool state)
{
	ShowCursor(state);
}

Vector2 keyBoard::moveCursorFrame(int x, int y)
{
	POINT p;
	GetCursorPos(&p);
	Vector2 move = Vector2(p.x - x, y - p.y);
	SetCursorPos(x, y);
	return move;
}