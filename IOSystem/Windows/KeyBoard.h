#pragma once
#include "Vector2.h"
#include "../IOstructures.h"

class keyBoard
{
public:
	keyBoard();
	~keyBoard();
	
	void create(WindowInputs& windowInput);
	void update();
	unsigned char* getState();
	unsigned char* getOldState();
	
	Vector2 getCursorPos();
	void showCursor(bool state);
	void setCursorPos(int x, int y);
	Vector2 moveCursorFrame(int x, int y);
private:
	unsigned char keyBoarState[256];
	unsigned char oldkeyBoarState[256];
};