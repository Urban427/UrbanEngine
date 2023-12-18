#pragma once
#include "Rect.h"

class AndroidFilter
{
	public:
	AndroidFilter();
	//~AndroidFilter();
	
	void setSize(int width, int height);
	Rect getInnerSize();
	Rect getCenter();
	
	char init();
	char broadcast();
	
	void initTime();
	double getDeltaTime();
private:
	int width;
	int height;
	int left;
	int top;
	int centerX;
	int centerY;
};
