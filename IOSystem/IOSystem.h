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
	
	Rect getInnerSize();
private:
	_Window _window;
};

