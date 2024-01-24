#pragma once
#include "Vector3.h"
#include "Quaternion.h"

class Transform
{
public:
	Transform();
	~Transform();
	
	
public:
	Vector3 	position;
	Quaternion	rotation;
	Vector3 	scale;
	
	unsigned int childCount;
	Transform* parent;
};



class GameObject
{
public:
	GameObject();
	~GameObject();
	
public:
	Transform transform;
private:
	
};