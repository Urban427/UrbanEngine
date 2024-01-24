#pragma once
//#include <memory>
#include "Vector3.h"

struct Vertex
{
	Vector3 pos;
	Vector2 ui;
};


typedef struct VertexBufferDesc
{
	void* verticlesList = nullptr;
	unsigned int vertexSize = 0;
	unsigned int listSize = 0;
}VertexBufferDesc;



class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferDesc& desc);
	void init(const VertexBufferDesc& desc);
	~VertexArrayObject();
	
	unsigned int getID();
	unsigned int getVertexSize();
private:
	unsigned int vertexBufferID;
	unsigned int vertexArrayObjectID;
	VertexBufferDesc vertexBufferData;
};


//typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
