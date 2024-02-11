#include "_array.h"
#include <bitset>
#include <stdio.h>


const unsigned int Number_of_components = 64;


unsigned int id_counter = 0;
template<class T>
unsigned int GetID()
{
	static unsigned int id = id_counter++;
	return id;
}

struct EntityDesc
{
	unsigned long long id;
	std::bitset<Number_of_components> components_mask;
};


struct ComponentPool
{
	ComponentPool(size_t element_size)
	{
		this->element_size = element_size;
		components = new char[element_size * Number_of_components];
	}
	
	~ComponentPool()
	{
		delete[] components;
	}
	
	void* get(size_t index)
	{
		return components + element_size * index;
	}
	
	
	void* begin() 
	{
		return components;
	}
	
	char* components;
	size_t element_size;
};

class Scene
{
public:
	array<int> entities;
	array<ComponentPool> pools;
	
	unsigned long long addEntity()
	{
		printf("1\n");
		EntityDesc desc = {entities.size()};
		printf("1\n");
		entities.push_back(111);
		printf("1\n");
		return entities.back();
	}

	template<class T>
	T* Assign(unsigned long long entityID)
	{
		printf("here\n");
		size_t ComponentID = GetID<T>();
		printf("here\n");
		if(pools.size() <= ComponentID)
		{
			pools.push_back(ComponentPool(sizeof(T)));
		}
		printf("here\n");
		
		T* resComponent = new (pools[ComponentID].get(entityID)) T();
		printf("here\n");
		//entities[entityID].components_mask.set(ComponentID);
		printf("here\n");
		return resComponent;
	}
	
	template<class T>
	T* Get(unsigned long long entityId)
	{
		size_t ComponentID = GetID<T>();
		//if(entities[entityId].components_mask.test(ComponentID) == 0)
		{
			return nullptr;
		}
		
		return pools[ComponentID].get(entityId);
	}
};




