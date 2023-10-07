#pragma once

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	//~Vector2();

	float length();
public:
	float x = 0;
	float y = 0;
};