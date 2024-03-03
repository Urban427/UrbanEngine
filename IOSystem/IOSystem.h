#pragma once
#include "Rect.h"
#include "Vector2.h"
#include "Vector3.h"
#include "IOstructures.h"
#include "FBXfile.h"

#ifdef android
	#include "AndroidInputManager.h"
	#include "AndroidFilter.h"
	#include "AndroidFileManager.h"
	#define _Window AndroidFilter 
	#define _Input AndroidInputManager
#elif windows
	#include "Window.h"
	#include "KeyBoard.h"
	#include "winFileManager.h"
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
	
	Vector3* readFBX(const char* filename);
};

