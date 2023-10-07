#pragma once
#include "Vector2.h"

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	//~Vector3();
	
	float length();
public:
	float x = 0;
	float y = 0;
	float z = 0;
};