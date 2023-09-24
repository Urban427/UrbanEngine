#include "UniformObject.h"

#ifdef glad
	#include "glad/glad.h"
#elif gles2
	#include "gles2/gl2.h"
#endif

UniformObject::UniformObject(const UniformDesc& desc)
{
	init(desc);
}

void UniformObject::init(const UniformDesc& desc)
{
	valueLocation = glGetUniformLocation(desc.shaderID, desc.valueName);
	setValue(desc.value);
}

//UniformObject::~UniformObject() {}

void UniformObject::setValue(int value)
{
	this->value = value;
	glUniform1i(valueLocation, value);
}

unsigned int UniformObject::getValue()
{
	return value;
}