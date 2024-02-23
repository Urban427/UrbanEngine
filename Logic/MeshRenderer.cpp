#include "MeshRenderer.h"

void RenderSystem::AddLOD(const LOD lod, size_t entity)
{
	//if(entity.hasLOD)
	{
		//return;
	}
	
	if(onlyLODS.sparseArray.size() <= entity)
	{
		onlyLODS.sparseArray.resize(entity + 1, -1);
	}
	
	
}

void RenderSystem::AddMeshRenderer(const MeshRenderer meshRenderer, size_t entity)
{
	
}

LOD* RenderSystem::GetLOD(size_t entity)
{
	return nullptr;
}

MeshRenderer* RenderSystem::GetMeshRenderer(size_t entity)
{
	return nullptr;
}

void RenderSystem::RemoveLOD(size_t entity)
{
	
}

void RenderSystem::RemoveMeshRenderer(size_t entity)
{
	
}

void RenderSystem::Render()
{
	
}