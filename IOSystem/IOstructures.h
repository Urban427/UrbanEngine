#pragma once
#include "Vector2.h"
#include "string.h"

//input
struct WindowInputs
{
	unsigned char* 	 states = nullptr;
	Vector2*		 poses  = nullptr;
	Vector2*		 oldPoses  = nullptr;
	
	unsigned int number = 0;
};




//files
struct CFile
{
	char* start = nullptr;
	char* pointer = nullptr;
	unsigned int size = 0;
};


char readCFile(void* value, int value_size, CFile& file);