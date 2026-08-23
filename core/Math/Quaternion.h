#pragma once
#include "Vector3.h"

class Quaternion
{
public:
	Quaternion() : x(0), y(0), z(0), w(1) {};
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	void normalize();
	static Quaternion Inverse(const Quaternion q);
	static Quaternion FromEuler(float pitch, float yaw, float roll);
	static Quaternion FromAxisAngle(const Vector3& axis, float angle);
	static Quaternion LookRotation(Vector3 direction, Vector3 up);

public:
	Quaternion operator+(const Quaternion q);
	Quaternion operator-(const Quaternion q);
	inline Quaternion  operator*(const Quaternion& b);
	inline Quaternion& operator*=(const Quaternion& b);
	Quaternion operator*(const float b);
	Vector3 operator*(const Vector3 v);

public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1;
};


inline Quaternion Quaternion::LookRotation(Vector3 direction, Vector3 up) {
	Vector3 right = Vector3::Cross(up, direction);
    up = Vector3::Cross(direction, right);

    float m00 = right.x;
    float m01 = right.y;
    float m02 = right.z;

    float m10 = up.x;
    float m11 = up.y;
    float m12 = up.z;

    float m20 = direction.x;
    float m21 = direction.y;
    float m22 = direction.z;

    float trace = m00 + m11 + m22;

    Quaternion q;
    if (trace > 0.0f) {
        float s = sqrt(trace + 1.0f) * 2.0f;
        q.w = 0.25f * s;
        q.x = (m21 - m12) / s;
        q.y = (m02 - m20) / s;
        q.z = (m10 - m01) / s;
    }
    else if (m00 > m11 && m00 > m22) {
        float s = sqrt(1.0f + m00 - m11 - m22) * 2.0f;
        q.w = (m21 - m12) / s;
        q.x = 0.25f * s;
        q.y = (m01 + m10) / s;
        q.z = (m02 + m20) / s;
    }
    else if (m11 > m22) {
        float s = sqrt(1.0f + m11 - m00 - m22) * 2.0f;
        q.w = (m02 - m20) / s;
        q.x = (m01 + m10) / s;
        q.y = 0.25f * s;
        q.z = (m12 + m21) / s;
    }
    else {
        float s = sqrt(1.0f + m22 - m00 - m11) * 2.0f;
        q.w = (m10 - m01) / s;
        q.x = (m02 + m20) / s;
        q.y = (m12 + m21) / s;
        q.z = 0.25f * s;
    }
    return q;
}

inline Quaternion Quaternion::FromAxisAngle(const Vector3& axis, float angle)
{
    float halfAngle = angle * 0.5f;

    float s = sin(halfAngle);
    float c = cos(halfAngle);

    Quaternion q;
    q.x = axis.x * s;
    q.y = axis.y * s;
    q.z = axis.z * s;
    q.w = c;

    return q;
}

inline Quaternion Quaternion::FromEuler(float pitch, float yaw, float roll)
{
    float d2r = Math::PI / 180.0f;

    pitch *= d2r;
    yaw   *= d2r;
    roll  *= d2r;

    Quaternion qx = Quaternion::FromAxisAngle(Vector3(1,0,0), pitch);
    Quaternion qy = Quaternion::FromAxisAngle(Vector3(0,1,0), yaw);
    Quaternion qz = Quaternion::FromAxisAngle(Vector3(0,0,1), roll);

    // FPS-style order (VERY IMPORTANT)
    return qy * qx * qz;
}

inline Quaternion Quaternion::operator*(const Quaternion& b)
{
	return Quaternion(
		 x * b.w + y * b.z - z * b.y + w * b.x,
		-x * b.z + y * b.w + z * b.x + w * b.y,
		 x * b.y - y * b.x + z * b.w + w * b.z,
		-x * b.x - y * b.y - z * b.z + w * b.w);
}

inline Quaternion& Quaternion::operator*=(const Quaternion& b)
{
	float newX =   x * b.w + y * b.z - z * b.y + w * b.x;
	float newY =  -x * b.z + y * b.w + z * b.x + w * b.y;
	float newZ =   x * b.y - y * b.x + z * b.w + w * b.z;
	float newW =  -x * b.x - y * b.y - z * b.z + w * b.w;
	
	this->x = newX;
	this->y = newY;
	this->z = newZ;
	this->w = newW;
	return *this;
}

inline Vector3 Quaternion::operator*(const Vector3 v)
{
	Quaternion q = *this * Quaternion(v.x, v.y, v.z, 0) * Inverse(*this);
	return Vector3(q.x, q.y, q.z);
}