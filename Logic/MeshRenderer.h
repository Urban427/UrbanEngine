#pragma once
#include <vector>

struct MeshRenderer
{
	unsigned int meshIndex;
	unsigned int materialIndex;
};

struct LOD
{
	unsigned int entity;
	float min;
	float max;
};

struct MeshRendererLOD: MeshRenderer, LOD{};


template<class T>
struct RenderComponentPool
{
	std::vector<T> array;
	std::vector<unsigned int> packedArray;
	std::vector<unsigned int> sparseArray;
};

class RenderSystem
{
public:
	RenderSystem() {};
	~RenderSystem() {};
	
	void AddLOD(const LOD lod, unsigned int entity);
	void AddMeshRenderer(const MeshRenderer meshRenderer, unsigned int entity);
	LOD* GetLOD(unsigned int entity);
	MeshRenderer* GetMeshRenderer(unsigned int entity);
	void RemoveLOD(unsigned int entity);
	void RemoveMeshRenderer(unsigned int entity);
	void Render();
private:
	RenderComponentPool<MeshRenderer> onlyMeshes;
	RenderComponentPool<MeshRendererLOD> both;
	//will ignore him in render method
	RenderComponentPool<LOD> onlyLODS;
	
};