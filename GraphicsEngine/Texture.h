#pragma once
#include "structures.h"

class Texture
{
public:
	Texture(const TextureStruct desc);
	void init(const TextureStruct desc);
	//~Texture();
	
	unsigned int getID();
public:
	unsigned int textureID;
	
	
	unsigned int width;
	unsigned int height;
};