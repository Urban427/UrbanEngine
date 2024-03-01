#pragma once
#include "Vector2.h"

struct WindowInputs
{
	unsigned char* 	 states = nullptr;
	Vector2*		 poses  = nullptr;
	Vector2*		 oldPoses  = nullptr;
	
	unsigned int number = 0;
};



struct CFile
{
	char* start = nullptr;
	char* pointer = nullptr;
	unsigned int size = 0;
};