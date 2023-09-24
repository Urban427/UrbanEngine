#pragma once
#include "Rect.h"

#ifdef android
	#include "AndroidFilter.h"
	#define _Window AndroidFilter 
#elif windows
	#include "Window.h"
	#define _Window Window 
#endif

class IOSystem
{
public:
	IOSystem();
	~IOSystem();

	char onCreate();
	char onUpdate();
	
	double getTime();
	
	void setSize(unsigned int width, unsigned int height);
	Rect getInnerSize();
private:
	_Window _window;
};

