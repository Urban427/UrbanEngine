#pragma once

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	//~Vector2();

	float length();
	float squareLength();
	Vector2 normalized();
public:
	Vector2 operator+(const Vector2& b);
	Vector2 operator-();
	Vector2 operator-(const Vector2& b);
	Vector2 operator*(float b);
	Vector2 operator/(float b);
	Vector2 operator+=(const Vector2& b);
	Vector2 operator-=(const Vector2& b);
	Vector2 operator*=(float b);
	bool operator==(const Vector2& b);
public:
	static float Distance(const Vector2& a, const Vector2& b);
	static float DistanceSquare(const Vector2& a, const Vector2& b);
public:
	float x = 0;
	float y = 0;
};

Vector2 operator*(float a, const Vector2& b);