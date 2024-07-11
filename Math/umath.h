#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix4x4.h"


struct Vertex
{
	Vector3 pos;
	Vector3 normal;
	Vector2 uv;
};

struct Mesh
{
	int* index;
	int index_size;
	
	Vertex* vertex;
	int vertex_size;
	
	unsigned int* materials;
	unsigned int  number_of_materials;
};

struct TextureStruct
{
	int width;
	int height;
	int* pixels;
};

bool checkClockwise(Vector2 a, Vector2  b, Vector2 c);
bool inTrinagle(Vector2 a, Vector2  b, Vector2 c, Vector2 checkPoint);
void TriangulatePolygon(
	Vertex* vertex_array, Vector3 normal,
	Vector2* vector2_buffer, bool* removed_vertexes,
	int* index_array, int number_of_points,
	int* result_indices);

void freeMesh(Mesh& mesh);