#pragma once

struct MeshRenderer
{
	size_t meshIndex;
	size_t materialIndex;
};

struct LOD
{
	size_t entity;
	float min;
	float max;
};

struct MeshRendererLOD: MeshRenderer, LOD{};


template<class T>
struct RenderComponentPool
{
	vector<T> array;
	vector<size_t> packedArray;
	vector<size_t> sparseArray;
};

class RenderSystem
{
public:
	RenderSystem() {};
	~RenderSystem() {};
	
	void AddLOD(const LOD lod, size_t entity);
	void AddMeshRenderer(const MeshRenderer meshRenderer, size_t entity);
	LOD* GetLOD(size_t entity);
	MeshRenderer* GetMeshRenderer(size_t entity);
	void RemoveLOD(size_t entity);
	void RemoveMeshRenderer(size_t entity);
	void Render();
private:
	RenderComponentPool<MeshRenderer> onlyMeshes;
	RenderComponentPool<MeshRendererLOD> both;
	//will ignore him in render method
	RenderComponentPool<LOD> onlyLODS;
	
};