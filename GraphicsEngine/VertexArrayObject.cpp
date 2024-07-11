#include "VertexArrayObject.h"
#include <malloc.h>
#include "Vector3.h"

#ifdef glad
	#include "glad/glad.h"
#elif gles2
	#include "gles2/gl2.h"
#endif

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& desc)
{
	init(desc);
}

void VertexArrayObject::init(const VertexBufferDesc& desc)
{
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, desc.vertexSize * desc.listSize, desc.verticlesList, GL_STATIC_DRAW);
		
	
	glVertexAttribPointer(
		0, 
		sizeof(Vector3) / sizeof(float), 
		GL_FLOAT, 
		GL_FALSE, 
		desc.vertexSize,
		0
	);
	glEnableVertexAttribArray(0);
	
	
	glVertexAttribPointer(
		1, 
		sizeof(Vector3) / sizeof(float), 
		GL_FLOAT, 
		GL_FALSE, 
		desc.vertexSize,
		(void*)(sizeof(Vector3))
	);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(
		2, 
		sizeof(Vector2) / sizeof(float), 
		GL_FLOAT, 
		GL_FALSE, 
		desc.vertexSize,
		(void*)(sizeof(Vector3) + sizeof(Vector3))
	);
	glEnableVertexAttribArray(2);
	vertexBufferData = desc;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArrayObject::~VertexArrayObject()
{

}

unsigned int VertexArrayObject::getID()
{
	return vertexArrayObjectID;
}

unsigned int VertexArrayObject::getVertexSize()
{
	return vertexBufferData.vertexSize;
}