#include "ComponentManager.h"
#include <chrono>
#include <intrin.h>
#include <unistd.h>
#include <stdio.h>


#define number_of_objects 10000
#define nummberOftests 10000


//components
struct burning
{
	int potencial = 10000;
	int bruningPower = 3;
};

struct freezing
{
	int frezzenngPotencial = 20000;
	int frezzenngPower = 1;
};

struct winding
{
	int windingPotencial = 30000;
	int windinPower = 1;
};

class burn
{
public:
	burn() {};
	~burn() {};
	
	void updateBurn()
	{
		fr += power;
	}
private:
	int fr = 1;
	int power = 1;
};

class free
{
public:
	free() {};
	~free() {};
	
	void updateFree()
	{
		fr += power;
	}
private:
	int fr = 1;
	int power = 1;
};

class wind: public free
{
public:
	wind() {};
	~wind() {};
	
	void updateWind()
	{
		wi += power;
		free::updateFree();
	}
private:
	int wi = 1;
	int power = 1;
};

class object: public burn, public wind
{
public:
	object() {};
	~object() {};
	

	void update()
	{
		burn::updateBurn();
		wind::updateWind();
	}
};


void sysObj(object* obj, int size)
{
	for(int i = 0; i < size; i++)
	{
		(*obj++).update();
	}
}




void sysA(burning* b, int size)
{
	for(int i = 0; i < size; i++)
	{
		(*b++).potencial += (*b).bruningPower;
	}
}

void sysB(freezing* f, int size)
{
	for(int i = 0; i < size; i++)
	{
		(*f++).frezzenngPotencial += (*f).frezzenngPower;
	}
}


void sysC(winding* w, int size)
{
	for(int i = 0; i < size; i++)
	{
		(*w++).windingPotencial += (*w).windinPower;
	}
}



int main()
{
	
	unsigned long long ex12 = 0;
	//obj 1 burning upgrader frezzenng ....
	object objs[number_of_objects];
	for(int j = 0; j < nummberOftests; j++){
		object* ob = objs;
		unsigned long long st = __rdtsc();
		
		
		sysObj(ob, number_of_objects);
		
		
		unsigned long long end = __rdtsc();
		ex12 += end - st;
	}
	printf("oop: %llut\n",ex12 / nummberOftests);
	
	
	
	burning 	objsbu[number_of_objects] =  {};
	freezing 	objsfr[number_of_objects] =  {};
	winding 	objswi[number_of_objects] =  {};
	
	unsigned long long ex22 = 0;
	for(int j = 0; j < nummberOftests; j++){
		burning* b = objsbu;
		freezing* f = objsfr;
		winding* w = objswi;
		unsigned long long st = __rdtsc();
		
		
		sysA(b, number_of_objects);
		sysB(f, number_of_objects);
		sysC(w, number_of_objects);
		
		
		
		unsigned long long end = __rdtsc();
		ex22 += end -st;
	}
	printf("ecs: %llut\n", ex22 / nummberOftests);
	
	printf("win percent: %f\n", (float)ex12 / ex22);
	
	return 0;
} 