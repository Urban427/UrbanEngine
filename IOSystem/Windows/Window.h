#pragma once
#include <Windows.h>
#include "Rect.h"

class Window
{
public:
	Window();
	~Window();

	
	char init();
	char broadcast();
private:
	HWND _hwnd; 
	HDC hDC;
public:
	int width;
	int height;
};

