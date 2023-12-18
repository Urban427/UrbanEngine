#pragma once
#include <Windows.h>
#include "Rect.h"

class Window
{
public:
	Window();
	~Window();

	
	Rect getCenter();
	Rect getInnerSize();
	void setPos(int x, int y);
	void setSize(unsigned int width, unsigned int height);
	void onFocus();
	void onKillFocus();
	
	void initTime();
	double getDeltaTime();
	
	char init();
	char broadcast();
	
	static Window* get();
private:
	HWND _hwnd; 
	HDC hDC;
	long time;
	
	
	
	int width;
	int height;
	int left;
	int top;
	int centerX;
	int centerY;
};

