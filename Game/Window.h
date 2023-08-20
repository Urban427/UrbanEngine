#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

	char init();
	char broadcast();
private:
	HWND _hwnd; 
	HDC dummyDc;
public:
	bool status = 0;
};

