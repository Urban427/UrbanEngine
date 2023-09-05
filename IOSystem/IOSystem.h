#pragma once
#include "Rect.h"
#if defined(WIN32)
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
	
	Rect getInnerSize();
private:
	_Window _window;
};

