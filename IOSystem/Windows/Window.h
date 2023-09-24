#pragma once
#include <Windows.h>
#include "Rect.h"

class Window
{
public:
	Window();
	~Window();

	
	Rect getInnerSize();
	
	void setSize(unsigned int width, unsigned int height);
	double getTime();
	
	char init();
	char broadcast();
private:
	HWND _hwnd; 
	HDC hDC;
public:
	int width;
	int height;
};

