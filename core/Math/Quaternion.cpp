#include "Quaternion.h"
#include <math.h>

Quaternion Quaternion::Inverse(const Quaternion q)
{
	return Quaternion(-q.x, -q.y, -q.z, q.w);
}

void Quaternion::normalize()
{
	float length = sqrt(w * w + x * x + y * y + z * z);
	if (length == 0) {
		return;
	}
	x /= length;
	y /= length;
	z /= length;
	w /= length;
}


Quaternion Quaternion::operator+(const Quaternion q)
{
	return Quaternion(this->x + q.x, this->y + q.y, this->z + q.z, this->w + q.w);
}

Quaternion Quaternion::operator-(const Quaternion q)
{
	return Quaternion(this->x - q.x, this->y - q.y, this->z - q.z, this->w - q.w);
}


Quaternion Quaternion::operator*(const float b)
{
	return Quaternion(this->x * b, this->y * b, this->z * b, this->w * b);
}