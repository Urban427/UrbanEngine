#include "MeshRenderer.h"

void RenderSystem::AddLOD(const LOD lod, unsigned int entity)
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

void RenderSystem::AddMeshRenderer(const MeshRenderer meshRenderer, unsigned int entity)
{
	
}

LOD* RenderSystem::GetLOD(unsigned int entity)
{
	return nullptr;
}

MeshRenderer* RenderSystem::GetMeshRenderer(unsigned int entity)
{
	return nullptr;
}

void RenderSystem::RemoveLOD(unsigned int entity)
{
	
}

void RenderSystem::RemoveMeshRenderer(unsigned int entity)
{
	
}

void RenderSystem::Render()
{
	
}