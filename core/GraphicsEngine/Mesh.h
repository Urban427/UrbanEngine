#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <Graph.h>
#include "GraphicsEngine.h"

struct BoundingBox {
    Vector3 min;
    Vector3 max;
};

struct Vertex {
	Vector3 pos;
	Vector3 normal;
	Vector2 uv;
	Vector2 uv1;
};

class Mesh {
public:
	Mesh() {};
	Mesh(int *index, int index_size, Vertex *vertex, int vertex_size, unsigned int *materials, unsigned int number_of_materials);
	Mesh(Mesh&& mesh) noexcept;
	Mesh &operator=(Mesh &&mesh) noexcept;
	~Mesh();

	void syncWithGPU();
	void setMeshOnPipeline();
	void combineMaterials(int uniqueMaterials);
	void seperateMeshWithVoxels(int width, int height, int depth);
	int getNumberOfMaterials() { return materials.size(); }
	unsigned int getMaterialSize(int id) { 
		if(id >= materials.size()) return 0;
		return materials[id]; 
	};
	int trianglesSize() { return indices.size() / 3; }
	void getTriangle(int index, Vector3& a, Vector3& b, Vector3& c) { index *= 3; a = vertices[indices[index]].pos; b = vertices[indices[index + 1]].pos; c = vertices[indices[index + 2]].pos;}
	void splitTriangleAtCenter(int triangleIndex);
	ListGraph<float> buildGraph();

    BoundingBox getBoundingBox() const;
public:
    std::vector<uint32_t> indices;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> materials;

    VertexArrayObject* vao = nullptr;
    IndexArrayObject* iao = nullptr;
};

Mesh CreatePlane();
Mesh CreateCube();
Mesh CreateSphere(float radius = 0.5f, uint32_t stacks = 32, uint32_t slices = 32);
Mesh CreateCylinder(uint32_t slices = 32);
Mesh CreateCapsule(float height = 1.0f, float radius = 0.5f, uint32_t stacks = 32, uint32_t slices = 32);

