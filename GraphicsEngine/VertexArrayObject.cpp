#include "VertexArrayObject.h"
#include "glad/glad.h"

VertexArrayObject::VertexArrayObject(const VertexBufferData& data)
{
	glGenBuffers(1, &vertexBufferID);
	
	
	glGenVertexArrays(1, &vertexArrayObjectID);
	glBindVertexArray(vertexArrayObjectID);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, data.vertexSize * data.listSize, data.verticlesList, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data.vertexSize, 0);
	glEnableVertexAttribArray(0);
	
	glBindVertexArray(0);
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