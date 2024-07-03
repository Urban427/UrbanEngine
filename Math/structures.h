#pragma once
#include "Vector2.h"
#include "Vector3.h"

struct TextureStruct
{
	int width;
	int height;
	int* pixels;
};

struct Vertex
{
	Vector3 pos;
	Vector3 normal;
	Vector2 ui;
};