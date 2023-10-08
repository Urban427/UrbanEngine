#include "Math.h"
#include <math.h>
#include <stdio.h>

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

void generateSawArray(float* array, unsigned int size)
{
	int period = 5;
	float delta = 1.0f / size;
	float temp = 0;
	for(unsigned int i = 0; i < size; i++, array++, temp += delta)
	{
		float t = temp * period;
		*array = 0.3f * (t - (int)(t + 0.5f)) + 0.5f;
	}
}

void generateSinusArray(float* array, unsigned int size)
{
	float delta = 1.0f / size;
	float temp = 0;
	for(int i = 0; i < size; i++, array++, temp += delta)
	{
		*array = sin(54.3f * temp) / 4 + 0.5f;
	}
}

void generateStepsArray(float* array, unsigned int size)
{
	int period = 6;
	float delta = 1.0f / size;
	float temp = 0;
	for(unsigned int i = 0; i < size; i++, array++, temp += delta)
	{
		float t = (float)((int)(temp * period) % period)/ period;
		*array = t + sin(temp * 111) * 0.002f + 0.1f;
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
		//*array = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
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

void saveFileData(float* array, unsigned int size)
{
	FILE* file = fopen("save.data", "wb");
	
	fwrite(&size, sizeof(unsigned int), 1 , file);
	for(unsigned int i = 0; i < size; i++)
	{
		fwrite(&array[i], sizeof(unsigned int), 1 , file);
	}
	
	fclose(file);
}



void normalizePoints(float* array, unsigned int size)
{
	for(unsigned int i = 0; i < size; i++)
	{
		array[i] = array[i] * 0.8f + 0.1f;
	}
}