#pragma once
#if defined(WIN32)
	#include "Window.h"
#endif

class IOSystem
{
public:
	IOSystem();
	~IOSystem();

	char onCreate();
	char onUpdate();
private:
#if defined(WIN32)
	Window _window;
#endif
};

