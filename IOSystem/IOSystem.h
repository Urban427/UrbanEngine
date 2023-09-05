#pragma once
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
private:
	_Window _window;
};

