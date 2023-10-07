#include "Math.h"
#include <math.h>

static unsigned int seed = 0;

void setSeed(const unsigned int _seed)
{
	seed = _seed;
}


void generateConstArray(float* array, unsigned int size, const float number)
{
	for(unsigned int i = 0; i < size; i++, array++)
	{
		*array = number;
	}
}

void generateIncreasingArray(float* array, unsigned int size)
{
	float delta = 1.0f / (size - 1);
	float temp = 0;
	for(unsigned int i = 0; i < size; i++, array++, temp += delta)
	{
		*array = temp;
	}
}

void generateSquaredArray(float* array, unsigned int size)
{
	float delta = 1.0f / (size - 1);
	float temp = 0;
	for(unsigned int i = 0; i < size; i++, array++, temp += delta)
	{
		*array = temp * temp;
	}
}

void generateLowingArray(float* array, unsigned int size)
{
	float delta = 1.0f / (size - 1);
	float temp = 1.0f;
	for(unsigned int i = 0; i < size; i++, array++, temp -= delta)
	{
		*array = temp;
	}
}

void generateSawArray(float* array, unsigned int size, int period)
{
	float delta = 1.0f / (size - 1);
	float temp = 0;
	for(int i = 0; i < size; i++, array++, temp += delta)
	{
		*array = (float)abs((int)(temp * period * 5) % period - period / 2) / period + 0.25f;
	}
}

void generateSinusArray(float* array, unsigned int size)
{
	float delta = 1.0f / 33;
	float temp = 0;
	for(int i = 0; i < size; i++, array++, temp += delta)
	{
		*array = sin(0.3f * temp) / 4 + 0.5f;
	}
}

void randomArray(float* array, unsigned int size)
{
	float del2 = 2;
	float temp = 0;
	for(unsigned int i = seed; i < seed + size; i++, array++)
	{
		temp = 0;
		del2 = 2;
		for(unsigned int j = 0; j < 8 * sizeof(unsigned int); j++)
		{
			temp += ((i >> j) & 1) / del2;
			del2 *= 2;
		}
		*array = temp;
	}
}

void randomArray2(float* array, unsigned int size)
{
	int t = 3;
	
	float del2 = t;
	float temp = 0;
	for(unsigned int i = seed; i < seed + size; i++, array++)
	{
		unsigned int j = i;
		temp = 0;
		del2 = t;
		while(j > 0)
		{
			temp += (float)(j % t) / del2;
			j /= t;
			del2 *= t;
		}
		*array = temp;
	}
}