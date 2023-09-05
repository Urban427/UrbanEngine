#pragma once

typedef struct VertexBufferData
{
	void* verticlesList = nullptr;
	unsigned int vertexSize = 0;
}VertexBufferData;


class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferData& data);
	~VertexArrayObject();
	
private:
	unsigned int vertexBufferID;
	int* lol;
};