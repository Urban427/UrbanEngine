#pragma once

struct TextureDesc
{
	unsigned int width;
	unsigned int height;
	
	unsigned int* image;
};

class Texture
{
public:
	Texture(const TextureDesc& desc);
	void init(const TextureDesc& desc);
	//~Texture();
	
	unsigned int getID();
private:
	unsigned int textureID;
	
	
	unsigned int width;
	unsigned int height;
};