#include "ComponentManager.h"
#include <stdio.h>
#include <chrono>
#include <intrin.h>
#include <unistd.h>
#include <vector>
#include <bitset>
using namespace std;

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
	bitset<Number_of_components> components_mask;
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
	
	char* components;
	size_t element_size;
};

struct Scene
{
	vector<EntityDesc> entities;
	vector<ComponentPool> pools;
	
	unsigned long long addEntity()
	{
		entities.push_back({entities.size(), 0});
		return entities.back().id;
	}

	template<class T>
	T* Assign(unsigned long long entityID)
	{
		size_t ComponentID = GetID<T>();
		if(ComponentID >= pools.size())
		{
			pools.resize(ComponentID + 1, 0);
		}
		
		if(pools[ComponentID].element_size == 0)
		{
			pools[ComponentID] = ComponentPool(sizeof(T));
		}
		
		
		T* resComponent = (T*)pools[ComponentID].get(entityID);
		*resComponent = T();
		entities[entityID].components_mask.set(ComponentID);
		return resComponent;
	}
	
	template<class T>
	T* Get(unsigned long long entityId)
	{
		size_t ComponentID = GetID<T>();
		if(entities[id].components_mask.test(ComponentID) == 0)
		{
			return nullptr;
		}
		
		return pools[ComponentID].get(entityId);
	}
};











//components
class burning
{
public:
	int potencial = 10000;
	int bruningPower = 3;
};

class freezing
{
public:
	int frezzenngPotencial = 20000;
	int frezzenngPower = 1;
};

class winding
{
public:
	int windingPotencial = 30000;
	int windinPower = 1;
};

class object: public burning, public freezing, public winding
{
public:
	void burningUpgrader(int f)
	{
		for(int i = 0; i < 10; i++){
			potencial -= bruningPower;
		}
		potencial -= f;
	}

	void freezingUpgrader(int f)
	{
		for(int i = 0; i < 10; i++){
			frezzenngPotencial += frezzenngPower;
		}
		frezzenngPotencial -= f;
	}

	void windingUpgrader(int f)
	{
		for(int i = 0; i < 10; i++){
			windingPotencial += windinPower;
		}
		windingPotencial -= f;
	}
};


//system
burning burningUpgrader(burning obj, int f)
{
	for(int i = 0; i < 10; i++){
		obj.potencial -= obj.bruningPower;
	}
	obj.potencial -= f;
	return obj;
}

freezing freezingUpgrader(freezing    obj, int f)
{
	for(int i = 0; i < 10; i++){
		obj.frezzenngPotencial += obj.frezzenngPower;
	}
	obj.frezzenngPotencial -= f;
	return obj;
}

winding windingUpgrader(winding    obj, int f)
{
	for(int i = 0; i < 10; i++){
		obj.windingPotencial += obj.windinPower;
	}
	obj.windingPotencial -= f;
	return obj;
} 



int main()
{	
	GetID<winding>();

	Scene scene;
	unsigned long long id1 	= scene.addEntity();
	unsigned long long id2 	= scene.addEntity();
	unsigned long long id3 	= scene.addEntity();
	burning* burn 			= scene.Assign<burning>(id3);
	winding* wind 			= scene.Assign<winding>(id3);
	for(size_t i = 0; i < Number_of_components; i++)
	{
		printf("%d", scene.entities[id3].components_mask[i] == 1);
	}
	printf("\n");

	


	int number_of_objects = 100000;
	int nummberOftests = 10000;
	
	unsigned long long ex12 = 0;
	unsigned long long ex1 = 0;
	//obj 1 burning upgrader frezzenng ....
	object* objs = new object[number_of_objects];
	for(int j = 0; j < nummberOftests; j++){
		
		unsigned long long st = __rdtsc();
		auto start_t = std::chrono::steady_clock::now();
		
		for(int i = 0; i < number_of_objects; i++)
		{
			objs[i].burningUpgrader(i);
			objs[i].freezingUpgrader(i);
			objs[i].windingUpgrader(i);
		}
		
		
		unsigned long long end = __rdtsc();
		auto end_t = std::chrono::steady_clock::now();
		
		ex12 += end - st;
		ex1 += std::chrono::duration_cast<std::chrono::nanoseconds>(end_t- start_t).count();
		//printf("%d %d %d ", objs[0].potencial, objs[0].frezzenngPotencial, objs[0].windingPotencial);
	}
	printf("%llu\n%llut\n", ex1 / nummberOftests, ex12 / nummberOftests);
	
	
	
	burning* 	objsbu = new burning[number_of_objects];
	freezing* 	objsfr = new freezing[number_of_objects];
	winding* 	objswi = new winding[number_of_objects];
	unsigned long long ex2 = 0;
	unsigned long long ex22 = 0;
	for(int j = 0; j < nummberOftests; j++){
		auto start_t = std::chrono::steady_clock::now();
		unsigned long long st = __rdtsc();
		
		//obj 1 burning upgrader frezzenng ....
		
		for(int i = 0; i < number_of_objects; i++)
		{
			objsbu[i] = burningUpgrader(objsbu[i], i);
		}
		
		for(int i = 0; i < number_of_objects; i++)
		{
			objsfr[i] = freezingUpgrader(objsfr[i], i);
		}
		
		for(int i = 0; i < number_of_objects; i++)
		{
			objswi[i] = windingUpgrader(objswi[i], i);
		}
		auto end_t = std::chrono::steady_clock::now();
		unsigned long long end = __rdtsc();
		//printf("%d %d %d ", objsbu[0].potencial, objsfr[0].frezzenngPotencial, objswi[0].windingPotencial);
		ex2 += std::chrono::duration_cast<std::chrono::nanoseconds>(end_t- start_t).count();
		ex22 += end -st;
	}
	printf("%llu\n%llut\n", ex2 / nummberOftests, ex22 / nummberOftests);
	
	printf("win percent: %f\n",  ((float)ex1 * 100 / ex2) - 100);
	printf("win2 percent: %f\n", ((float)ex12 * 100 / ex22) - 100);
	
	return 0;
} 