#pragma once
#include "Vector2.h"
#include <cmath>


struct Rigidbody
{
	Vector2 position;
	float mass;
	char charge;
	Vector2 velocity;
	
	float radiusSphere;
};

void simulatePhysic(Rigidbody* body, unsigned int size);