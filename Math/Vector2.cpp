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

float Vector2::Distance(const Vector2& a, const Vector2& b)
{
	float _x = b.x - a.x;
	float _y = b.y - a.y;
	
	return sqrt(_x * _x + _y * _y);
}
	
float Vector2::DistanceSquare(const Vector2& a, const Vector2& b)
{
	float _x = b.x - a.x;
	float _y = b.y - a.y;
	
	return _x * _x + _y * _y;
}



float Vector2::length()
{
	return sqrt(x * x + y * y);
}

float Vector2::squareLength()
{
	return x * x + y * y;
}


Vector2 Vector2::normalized()
{
	float _length = 1.0f / sqrt(x * x + y * y);
	return Vector2(x * _length, y * _length);
}

Vector2 Vector2::operator+(const Vector2& b)
{
	return Vector2(x + b.x, y + b.y);
}

Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator-(const Vector2& b)
{
	return Vector2(x - b.x, y - b.y);
}

Vector2 Vector2::operator*(float b)
{
	return Vector2(x * b, y * b);
}

Vector2 Vector2::operator/(float b)
{
	return Vector2(x / b, y / b);
}

Vector2 Vector2::operator+=(const Vector2& b)
{
	x += b.x;
	y += b.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& b)
{
	x -= b.x;
	y -= b.y;
	return *this;
}

Vector2 Vector2::operator*=(float b)
{
	x *= b;
	y *= b;
	return *this;
}

bool Vector2::operator==(const Vector2& b)
{
	return x == b.x && y == b.y;
}

Vector2 operator*(float a, const Vector2& b)
{
	return Vector2(a * b.x, a * b.y);
}