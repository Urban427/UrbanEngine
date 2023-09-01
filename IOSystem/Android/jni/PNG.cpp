#include "PNG.h"
#include "AndroidFileManager.h"
#include <malloc.h>

RawImageData readPng()
{
	RawImageData image;
	
	return image;
}

char* intToSTR(int x)
{
	if(x == 0)
	{
		char* res = (char*)malloc(2);
		res[0] = 48;
		res[1] = 0;
		return res;
	}
	int size = 0;
	int temp = x;
	while(temp != 0)
	{
		size++;
		temp /= 10;
	}
	char* res = (char*)malloc(size + 1);
	for(int i = 0; i < size; i++)
	{
		res[size - 1 - i] = 48 + x % 10;
		x /= 10;
	}
	res[size] = 0;
	return res;
}

RawImageData readBMPFile(const char* filename)
{
	RawImageData image;
	
	File *f = open(filename, "rb");

	short  bfType;
	int    bfSize;
	short  bfReserved1;
	short  bfReserved2;
	int    bfOffBits;
    read(&bfType, sizeof(short), 1, f);
    read(&bfSize, sizeof(int), 1, f);
    read(&bfReserved1, sizeof(short), 1, f);
    read(&bfReserved2, sizeof(short), 1, f);
    read(&bfOffBits, sizeof(int), 1, f);
	
	
	int    biSize;
	int    biWidth;
	int    biHeight;
	short   biPlanes;
	short   biBitCount;
	int    biCompression;
	int    biSizeImage; 
	int    biXPelsPerMeter;
	int    biYPelsPerMeter;
	int    biClrUsed;     
	int    biClrImportant;
	
	read(&biSize, sizeof(int), 1, f);
    read(&biWidth, sizeof(int), 1, f);
    read(&biHeight, sizeof(int), 1, f);
    read(&biPlanes, sizeof(short), 1, f);
    read(&biBitCount, sizeof(short), 1, f);
    read(&biCompression, sizeof(int), 1, f);
    read(&biSizeImage, sizeof(int), 1, f);
    read(&biXPelsPerMeter, sizeof(int), 1, f);
    read(&biYPelsPerMeter, sizeof(int), 1, f);
    read(&biClrUsed, sizeof(int), 1, f);
    read(&biClrImportant, sizeof(int), 1, f);
	
	//move to main data
	seek(f, bfOffBits, SET);
	
	
	
	//set texture's data
	image.width = biWidth;
	image.height = biHeight;
    image.data = (char*)malloc(biWidth * biHeight * biBitCount / 8);
	
	//helping values
	char temp = 0;
	unsigned int index = 0;
	void* pos;
	
	print((const char*)intToSTR(bfSize));
	
	return image;
}