#include "VertexArrayObject.h"
#include "glad/glad.h"

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& desc)
{
	glGenVertexArrays(1, &vertexArrayObjectID);
	glBindVertexArray(vertexArrayObjectID);
	
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, desc.vertexSize * desc.listSize, desc.verticlesList, GL_STATIC_DRAW);
	
	for(unsigned int i = 0; i < desc.attributesListSize; i++)
	{
		glVertexAttribPointer(
		i, 
		desc.attributesList[i].numElements, 
		GL_FLOAT, 
		GL_FALSE, 
		desc.vertexSize,
		(void*)((i == 0)?0: desc.attributesList[i - 1].numElements * sizeof(float))
		);
		glEnableVertexAttribArray(i);
	}
	
	glBindVertexArray(0);
	
	vertexBufferData = desc;
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vertexArrayObjectID);
}

unsigned int VertexArrayObject::getID()
{
	return vertexArrayObjectID;
}

unsigned int VertexArrayObject::getVertexBufferSize()
{
	return vertexBufferData.listSize;
}

unsigned int VertexArrayObject::getVertexSize()
{
	return vertexBufferData.vertexSize;
}