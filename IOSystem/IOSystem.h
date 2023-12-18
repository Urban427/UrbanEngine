#pragma once
#include "Rect.h"
#include "Vector2.h"
#include "IOstructures.h"

#ifdef android
	#include "AndroidInputManager.h"
	#include "AndroidFilter.h"
	#define _Window AndroidFilter 
	#define _Input AndroidInputManager
#elif windows
	#include "Window.h"
	#include "keyBoard.h"
	#define _Window Window 
	#define _Input keyBoard
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
	Rect getCenter();

	//input
	void  createInputState();
	void  updateInputState();
	void  setInput(float x, float y);
	unsigned char* getInputState();
	unsigned char* getOldInputState();
	void showCursor(bool state);
	
	Vector2 moveCursor();
private:
	WindowInputs windowInputs;

	_Window _window;
	_Input  _input;
};

