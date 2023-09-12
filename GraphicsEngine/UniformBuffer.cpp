#include "UniformBuffer.h"

#ifdef glad
	#include "glad/glad.h"
#elif gles2
	#include "gles2/gl2.h"
#endif

UniformBuffer::UniformBuffer(const UniformBufferDesc& desc)
{
	init(desc);
}


UniformBuffer::~UniformBuffer()
{
	glDeleteBuffers(1, &id);
}

void UniformBuffer::init(const UniformBufferDesc& desc)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_UNIFORM_BUFFER, id);
	glBufferData(GL_UNIFORM_BUFFER, desc.size, nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	
	size = desc.size;
}

unsigned int UniformBuffer::getID()
{
	return id;
}