#include "Vector2.h"
#include <math.h>

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
public:
	inline Vector3(): x(0), y(0), z(0) {};
	inline Vector3(const Vector3& vec3): x(vec3.x), y(vec3.y), z(vec3.z) {};
	inline Vector3(float x, float y, float z): x(x), y(y), z(z) {};
	
	float length();
	
	inline float sqrMagnitude()
	{
		return x * x + y * y + z * z;
	}
	
	inline Vector3 normalized()
	{
		float l = sqrt(x * x + y * y + z * z);
		if(l == 0) {
			return Vector3(0, 0, 0);
		}
		return Vector3(x / l, y / l, z / l);
	}
public:
	static float Distance(Vector3 a, Vector3 b);
	static inline float SqrDistance(Vector3 a, const Vector3& b)
	{
		a -= b;
		return a.x * a.x + a.y * a.y + a.z * a.z; 
	}
	static Vector3 Cross(Vector3 a, Vector3 b);
public:
	Vector3 operator*(const float b);
	
	inline void operator*=(const float b)
	{
		x *= b;
		y *= b;
		z *= b;
	}
	
	Vector3 operator+(const Vector3 vec3);
	Vector3 operator-(const Vector3& vec3);
	
	inline void operator+=(const Vector3 vec3)
	{
		this->x += vec3.x;
		this->y += vec3.y;
		this->z += vec3.z;
	}
	
	inline void operator-=(const Vector3 vec3)
	{
		this->x -= vec3.x;
		this->y -= vec3.y;
		this->z -= vec3.z;
	}
	
	float operator[](const int index);
public:
	float x = 0;
	float y = 0;
	float z = 0;
};


#endif // VECTOR3_H