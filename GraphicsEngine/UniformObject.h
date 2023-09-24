#pragma once

struct UniformDesc
{
	unsigned int shaderID;
	const char* valueName;
	int value;
};

class UniformObject
{
public:
	UniformObject(const UniformDesc& desc);
	void init(const UniformDesc& desc);
	//~UniformObject();
	
	void setValue(int value);
	unsigned int getValue();
private:
	unsigned int valueLocation;
	int value;
};