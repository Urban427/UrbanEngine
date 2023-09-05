#pragma once
#include <memory>

typedef struct VertexBufferData
{
	void* verticlesList = nullptr;
	unsigned int vertexSize = 0;
	unsigned int listSize = 0;
}VertexBufferData;

class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferData& data);
	~VertexArrayObject();
	
	unsigned int getID();
private:
	unsigned int vertexBufferID;
	unsigned int vertexArrayObjectID;
};


typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
