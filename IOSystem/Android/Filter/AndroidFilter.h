#pragma once
#include "Rect.h"

class AndroidFilter
{
	public:
	AndroidFilter();
	~AndroidFilter();

	void setSize(unsigned int width, unsigned int height);
	Rect getInnerSize();
	
	char init();
	char broadcast();
	
	double getTime();
private:
	//HWND _hwnd; 
	//HDC hDC;
public:
	int width;
	int height;
};
