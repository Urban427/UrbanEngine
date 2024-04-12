#pragma once
#include "Vector2.h"

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	//~Vector3();
	
	float length();
	Vector3 normalized();
public:
	static float Distance(Vector3 a, Vector3 b);
	static float SqrDistance(Vector3 a, Vector3 b);
	static Vector3 Cross(Vector3 a, Vector3 b);
public:
	Vector3 operator*(const float b);
	Vector3 operator-(const Vector3 vec3);
	void operator+=(const Vector3 vec3);
	void operator-=(const Vector3 vec3);
	float operator[](const int index);
public:
	float x = 0;
	float y = 0;
	float z = 0;
};