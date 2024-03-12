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

Vector3 Vector3::normalized()
{
	float l = length();
	if(l == 0)
	{
		return Vector3(0, 0, 0);
	}
	return Vector3(x / l, y / l, z / l);
}

Vector3 Vector3::operator*(const float b)
{
	return Vector3(this->x * b, this->y * b, this->z * b);
}


Vector3 Vector3::operator+=(const Vector3& vec3)
{
	this->x += vec3.x;
	this->y += vec3.y;
	this->z += vec3.z;
	return *this;
}

float Vector3::operator[](const int index)
{
	switch(index)
	{
		case(0):
		{
			return x;
		}
		case(1):
		{
			return y;
		}
		default:
		{
			return z;
		}
	}
	return z;
}