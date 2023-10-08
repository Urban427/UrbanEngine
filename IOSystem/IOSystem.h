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
	
	//time
	void initTime();
	double getDeltaTime();

	//window
	void setSize(unsigned int width, unsigned int height);
	Rect getInnerSize();

	//input
	void createInputState();
	void updateInputState();
private:
	_Window _window;
};

