#include "Quaternion.h"
#include <math.h>

Quaternion::Quaternion()
{
	
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

//Quaternion::~Quaternion(){}


Quaternion Quaternion::operator+(const Quaternion& q)
{
	return Quaternion(this->x + q.x, this->y + q.y, this->z + q.z, this->w + q.w);
}

Quaternion Quaternion::operator*(const float& b)
{
	return Quaternion(this->x * b, this->y * b, this->z * b, this->w * b);
}
