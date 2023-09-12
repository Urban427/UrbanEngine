#pragma once
#include "Rect.h"

class AndroidFilter
{
	public:
	AndroidFilter();
	~AndroidFilter();

	
	Rect getInnerSize();
	
	char init();
	char broadcast();
private:
	//HWND _hwnd; 
	//HDC hDC;
public:
	int width;
	int height;
};
