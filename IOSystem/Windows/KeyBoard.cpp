#include "KeyBoard.h"
#include <Windows.h>

keyBoard::keyBoard()
{
	
}

keyBoard::~keyBoard()
{
	
}

void keyBoard::create()
{
	windowInput.number 		= 1;
	windowInput.states 		= new unsigned char(0);
	windowInput.poses  		= new Vector2(0, 0);
	windowInput.oldPoses  	= new Vector2(0, 0);
	
	
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
	unsigned char* ptrA = keyBoarState;
	unsigned char* ptrB = oldkeyBoarState;
	for(unsigned int i = 0; i < 256; i++)
	{
		(*ptrB) = (*ptrA);
		ptrA++;
		ptrB++;
	}
	if(GetKeyboardState(keyBoarState) == 0) { }
	
	
	POINT p;
	GetCursorPos(&p);
	*(windowInput.states)  	= *(keyBoarState + 1) & 0x80;
	*(windowInput.oldPoses) = *(windowInput.poses);
	*(windowInput.poses)    = Vector2(p.x, p.y);
}


unsigned char* keyBoard::getInputState()
{
	return keyBoarState;
}

unsigned char* keyBoard::getOldInputState()
{
	return oldkeyBoarState;
}


Vector2 keyBoard::getCursorPos()
{
	return *(windowInput.poses);
}

void keyBoard::setCursorPos(int x, int y)
{
	*(windowInput.poses) = Vector2(x, y);
	SetCursorPos(x, y);
}

void keyBoard::setCursorPosWithoutMoving()
{
	POINT p;
	GetCursorPos(&p);
	*(windowInput.poses)    = Vector2(p.x, p.y);
}

Vector2 keyBoard::deltaCursorPos()
{
	return (*windowInput.poses) - (*windowInput.oldPoses);
}

Vector2* keyBoard::getPos()
{
	return windowInput.poses;
}

Vector2* keyBoard::getOldPos()
{
	return windowInput.oldPoses;
}