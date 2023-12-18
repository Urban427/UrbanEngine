#pragma once
#include "Vector2.h"
#include "../../IOstructures.h"

class AndroidInputManager
{
public:
	AndroidInputManager();
	//~AndroidInputManager();
	
	void create(WindowInputs& windowInput);
	void update();
	unsigned char* getState();
	unsigned char* getOldState();
	
	void showCursor(bool state);
	void setCursorPos(int x, int y);
	Vector2 getCursorPos();
	Vector2 moveCursorFrame(int x, int y);
private:
	unsigned char keys[256] = {0};
	unsigned char oldKeys[256] = {0};
};