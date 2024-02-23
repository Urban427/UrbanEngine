#pragma once
#include "Rect.h"
#include "Vector2.h"
#include "IOstructures.h"

#ifdef android
	#include "AndroidFileManager.h"
	#include "AndroidInputManager.h"
	#include "AndroidFilter.h"
	#define _Window AndroidFilter 
	#define _Input AndroidInputManager
#elif windows
	#include "winFileManager.h"
	#include "Window.h"
	#include "KeyBoard.h"
	#define _Window Window 
	#define _Input keyBoard
#endif

class IOSystem: public _Input, public _Window, public FileManager
{
public:
	IOSystem();
	//~IOSystem();

	void onCreate(const char* windowName, int width, int height, bool fullscreen);
	void onUpdate();
	
	//time
	void initTime();
	double getDeltaTime();
	
	//input
	void setCenterCursorPos();
};

