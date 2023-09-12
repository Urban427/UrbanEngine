#pragma once

typedef struct UniformBufferDesc
{
	unsigned int size = 0;
}UniformBufferDesc;

class UniformBuffer
{
public:
	UniformBuffer(const UniformBufferDesc& desc);
	~UniformBuffer();
	
	void init(const UniformBufferDesc& desc);

	unsigned int getID();
private:
	unsigned int id;
	unsigned int size = 0;
};
