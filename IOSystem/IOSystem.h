#pragma once
#include "Rect.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "IOstructures.h"
#include "FBXfile.h"
#include <math.h>
#include <vector>
#include <umath.h>
//#define epsilon 0.000000000000000000000000000000000000001f

struct Point
{
	int index;
	int uv_index;
	Vector3 normal;
	
	bool operator==(const Point second)
	{
		if(this->uv_index == second.uv_index && 
		(this->normal.x == second.normal.x) && (this->normal.y == second.normal.y) && (this->normal.z == second.normal.z))
		{
			return 1;
		}
		return 0;
	}
};

#ifdef Android
	#include "AndroidInputManager.h"
	#include "AndroidFilter.h"
	#include "AndroidFileManager.h"
	#define _Window AndroidFilter 
	#define _Input AndroidInputManager
#elif windows
	#include "Window.h"
	#include "KeyBoard.h"
	#define _Window Window 
	#define _Input keyBoard
#endif

class IOSystem: public _Input, public _Window
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
	
	Mesh readFBX(const char* filename);
	TextureStruct readBMP(const char* filename);
};

