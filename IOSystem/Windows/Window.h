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
	int* buffer;
	int width;
	int height;

	bool status = 0;
};

