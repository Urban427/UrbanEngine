#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
{
	
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

//Vector2::~Vector2(){}

float Vector2::length()
{
	return sqrt(x * x + y * y);
}