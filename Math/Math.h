#pragma once

void generateConstArray(float* array, unsigned int size, const float number);
void generateIncreasingArray(float* array, unsigned int size);
void generateSquaredArray(float* array, unsigned int size);
void generateLowingArray(float* array, unsigned int size);
void generateSawArray(float* array, unsigned int size);
void generateSinusArray(float* array, unsigned int size);
void generateStepsArray(float* array, unsigned int size);
void randomArray(float* array, unsigned int size);
void randomArray2(float* array, unsigned int size);
void setSeed(const unsigned int _seed);


void saveFileData(float* array, unsigned int size);