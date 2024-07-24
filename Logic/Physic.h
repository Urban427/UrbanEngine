#pragma once
#include "Transform.h"
#include <iostream>

inline void calculateCollisions(Transform& a, Transform& b)
{	
	Vector3 posA(a.position);
	Vector3 posB(b.position);
	float size = 0.1f;
	float sizesqr(size);
	sizesqr *= size;
	Vector3 delta(posA);
	sizesqr *= 4;
	delta -= posB;
	float dist = delta.sqrMagnitude();
	if(dist < sizesqr)
	{
		if(dist == 0) 	{
			a.position += Vector3(static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand())).normalized();
            return;
		}
		
		//delta = delta.normalized();
		
		dist = size * Q_rsqrt(dist) - 0.5f;
		delta *= dist;
		posA += delta;
		a.position = posA;
		posB -= delta;
		b.position = posB;
	}
}

inline void simulatePhysicStep(Transform* transform, int size)
{
	for(int i = 1 ; i < size ; i++)
	{
		for(int j = i + 1 ; j < size; j++)
		{
			calculateCollisions(transform[i], transform[j]);
		}
		transform[i].position += Vector3(0, -0.003, 0);
		transform[i].position.x = clamp(-1, 1, transform[i].position.x);
		transform[i].position.y = clamp(  0, 10, transform[i].position.y);
		transform[i].position.z = clamp(-1, 1, transform[i].position.z);
	}
}

void calculatePhysic(Transform* transform, int size)
{
	for(int i = 0; i < 8; i++)
	{
		simulatePhysicStep(transform, size);
	}
}

