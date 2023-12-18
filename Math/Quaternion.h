#pragma once

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	//~Quaternion();
	
public:
	Quaternion operator+(const Quaternion& q);
	Quaternion operator*(const float& b);
public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;
};