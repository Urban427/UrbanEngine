#pragma once
#include "stdlibInclude.h"
#include "umath.h"

class DepthTexture {
public:
	DepthTexture() 														{ init(); }
	DepthTexture(int width, int height): width(width), height(height) 	{ init(); }
	~DepthTexture() 													{ destroy(); }
	
	inline unsigned int getDepthTexture() const	{ return depthTexture; }
	inline std::pair<int, int>  getSize() const	{ return {width, height}; }
	
	TextureStruct getTextureData();
	void bind();
	void unbind();
private:
	void init();
	void destroy();
private:
	unsigned int fbo = 0;
	unsigned int depthTexture = 0;
	
	int width = 1980;
	int height = 1080;
};