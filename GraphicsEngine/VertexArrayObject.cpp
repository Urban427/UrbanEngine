#include "VertexArrayObject.h"

#ifdef glad
	#include "glad/glad.h"
#elif gles2
	#include "gles2/gl2.h"
#endif

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& desc)
{
	#ifdef glad
	glGenVertexArrays(1, &vertexArrayObjectID);
	glBindVertexArray(vertexArrayObjectID);
	#endif
	
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, desc.vertexSize * desc.listSize, desc.verticlesList, GL_STATIC_DRAW);
	
	
	glVertexAttribPointer(
		0, 
		desc.attributesList[0].numElements, 
		GL_FLOAT, 
		GL_FALSE, 
		0,
		0);
	glEnableVertexAttribArray(0);
	
	#ifdef glad
	glBindVertexArray(0);
	#endif
	
	vertexBufferData = desc;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArrayObject::init(const VertexBufferDesc& desc)
{
	#ifdef glad
	glGenVertexArrays(1, &vertexArrayObjectID);
	glBindVertexArray(vertexArrayObjectID);
	#endif
	
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, desc.vertexSize * desc.listSize, desc.verticlesList, GL_STATIC_DRAW);
		
	for(int i = 0; i < desc.attributesListSize; i++)
	{	
		glVertexAttribPointer(
			i, 
			desc.attributesList[i].numElements, 
			GL_FLOAT, 
			GL_FALSE, 
			desc.vertexSize,
			(void*)((i == 0)?0:sizeof(float) * desc.attributesList[i - 1].numElements)
		);
		glEnableVertexAttribArray(i);
	}	
	
	#ifdef glad
	glBindVertexArray(0);
	#endif
	
	vertexBufferData = desc;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArrayObject::~VertexArrayObject()
{
	#ifdef glad
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vertexArrayObjectID);
	#endif
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