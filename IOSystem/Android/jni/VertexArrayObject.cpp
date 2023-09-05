#include "VertexArrayObject.h"
#include "gl2.h"

VertexArrayObject::VertexArrayObject(const VertexBufferData& data)
{
	glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, data.vertexSize, data.verticlesList, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data.vertexSize, 0);
    glEnableVertexAttribArray(0);
}


VertexArrayObject::~VertexArrayObject()
{
	//glDeleteBuffers(1, &vertexBufferID);
}