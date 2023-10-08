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
	
	void initTime();
	double getDeltaTime();
	
	char init();
	char broadcast();
private:
	HWND _hwnd; 
	HDC hDC;
	
	long time;
public:
	int width;
	int height;
};

