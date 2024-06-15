#pragma once
#include "Vector2.h"
#include "Vector3.h"

struct Vertex
{
	Vector3 pos;
	Vector2 ui;
	Vector3 normal;
};

class Vector4
{
public:
	Vector4();
	Vector4(float x, float y, float z, float w);
	//~Vector4();

	static Vector4 cross(const Vector4& v1, const Vector4& v2, const Vector4& v3);

public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;
};