#pragma once
#include <vector>
#include <bitset>

#include "Transform.h"
#include "MeshRenderer.h"

#define MAX_COMPONENTS_PER_OBJECT 32

struct Entity
{
	size_t id;
	std::bitset<MAX_COMPONENTS_PER_OBJECT> mask;
};


size_t id_counter = 0;
template<class T>
size_t GetID()
{
	static size_t id = id_counter++;
	return id;
}



class ComponentPool
{
public:
	ComponentPool(size_t structSize) 
	{
		this->structSize = structSize;
	};
	
	~ComponentPool() {};
	
	template<class T>
	T* AddComponent(size_t id)
	{
		size_t byteSize = (id + 1) * structSize;
		if(byteSize >= data.size())
		{
			data.resize(byteSize, 0);
		}
		return new (&data[id * structSize]) T();
	}
	
	template<class T>
	T* GetComponents()
	{
		return &data[0];
	}
	
	template<class T>
	T* GetComponent(size_t index)
	{
		return (T*)(&data[index * structSize]);
	}
private:
	size_t structSize;
	std::vector<char> data;
};


class ECS
{
public:
	ECS()
	{
		GetID<Transform>();
		GetID<MeshRenderer>();
		GetID<LOD>();
	}
	~ECS() {};
	
	size_t AddEntity()
	{
		entities.push_back({entities.size(), std::bitset<MAX_COMPONENTS_PER_OBJECT>()});
		return entities.back().id;
	}
	
	template<class T>
	T* AddComponent(size_t entityID)
	{
		size_t componentID = GetID<T>();
		if(pools.size() <= componentID)
		{
			pools.resize(componentID + 1, nullptr);
		}
		if(pools[componentID] == nullptr)
		{
			pools[componentID] = new ComponentPool(sizeof(T));
		}
		
		return pools[componentID]->AddComponent<T>(entityID);
	}
	
	template<class T>
	T* GetComponent(size_t entityID)
	{
		size_t componentID = GetID<T>();
		if(pools.size() <= componentID || pools[componentID] == nullptr)
		{
			return nullptr;
		}
		return pools[componentID]->GetComponent<T>(entityID);
	}
	
	template<class T>
	T* GetComponents()
	{
		size_t componentID = GetID<T>();
		if(pools.size() <= componentID || pools[componentID] == nullptr)
		{
			return nullptr;
		}
		return pools[componentID]->GetComponents<T>();
	}
	
public:
	std::vector<ComponentPool*> pools;
	std::vector<Entity> entities;
};