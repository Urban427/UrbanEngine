#include "Physic.h"


double G = 6.67f / pow(10, 11);
double deltatime = 0.03f * pow(10, 11);
double q_p = 1.6 / pow(10, 19);
double q_e = -1.6 / pow(10, 19);
double k = 9 * pow(10, 9);

Vector2 SphereCollision(Vector2 pos1, Vector2 pos2, float r1, float r2)
{
	Vector2 dir = pos1 - pos2;
	float distBitweenCenters = dir.squareLength();
	float minDist = r1 + r2;
	float minDistInSquare = minDist * minDist;
	
	
	if(distBitweenCenters > minDistInSquare / 4)
	{
		return Vector2(0, 0);
	}
	
	dir = dir.normalized();
	dir = dir * (sqrt(distBitweenCenters) - r1 + r2) / 4;
	
	return dir;
}

void bodysCollision(Rigidbody& a, Rigidbody& b)
{
	Vector2 dir = SphereCollision(a.position, b.position, a.radiusSphere, b.radiusSphere) / 2;
	if(dir == Vector2(0, 0))
	{
		return;
	}
	
	float E = 0.003f;
	
	Vector2 q = (1 + E) * (a.mass * a.velocity + b.mass * b.velocity) / (a.mass + b.mass);
	a.velocity = -E * a.velocity + q;
	b.velocity = -E * b.velocity + q;
	
	a.position += dir;
	b.position -= dir;
}

void simulateGravity(Rigidbody& a, Rigidbody& b)
{
	Vector2 vector12 = b.position - a.position;
	float accelerationMinusMass = G / vector12.squareLength()       * deltatime;
	vector12 = vector12.normalized();
	
	a.velocity += accelerationMinusMass * b.mass * vector12;
	b.velocity += -1 * accelerationMinusMass * a.mass * vector12;
	
	a.position += a.velocity * deltatime;
	b.position += b.velocity * deltatime;
}

void simulateAtoms(Rigidbody& a, Rigidbody& b)
{
	Vector2 vector12 = b.position - a.position;
	float accelerationMinusMass = k * abs(a.charge) * q_p * abs(b.charge) * q_p  / vector12.squareLength()       * deltatime;
	vector12 = vector12.normalized();
	
	Vector2 deltaV = -1 * (b.charge == a.charge) * accelerationMinusMass * vector12;
	a.velocity += deltaV;
	b.velocity += -1 * deltaV;
	
	a.position += a.velocity * deltatime;
	b.position += b.velocity * deltatime;
}

void simulatePhysic(Rigidbody* body, unsigned int size)
{
	for(unsigned int i = 0; i < size - 1; i++)
	{
		for(unsigned int j = i + 1; j < size; j++)
		{
			simulateAtoms(body[i], body[j]);
			bodysCollision(body[i], body[j]);
		}
	}
}