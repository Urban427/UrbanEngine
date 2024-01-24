#pragma once
#include "Vector2.h"
#include "../IOstructures.h"

class keyBoard
{
public:
	keyBoard();
	~keyBoard();
	
	//main
	void create();
	void update();
	
	//keyBoard
	unsigned char* getInputState();
	unsigned char* getOldInputState();

	//cursor
	Vector2 getCursorPos();
	void setCursorPos(int x, int y);
	void setCursorPosWithoutMoving();
	Vector2 deltaCursorPos();
private:
	WindowInputs windowInput;
	
	unsigned char keyBoarState[256];
	unsigned char oldkeyBoarState[256];
};