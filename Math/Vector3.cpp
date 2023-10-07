#include "Vector3.h"
#include <math.h>

Vector3::Vector3()
{
	
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//Vector3::~Vector3(){}

float Vector3::length()
{
	return sqrt(x * x + y * y + z * z);
}