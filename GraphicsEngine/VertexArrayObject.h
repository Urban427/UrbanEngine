#pragma once
//#include <memory>

typedef struct VertexAttribute
{
	unsigned int numElements = 0;
}VertexAttribute;

typedef struct VertexBufferDesc
{
	void* verticlesList = nullptr;
	unsigned int vertexSize = 0;
	unsigned int listSize = 0;
	
	VertexAttribute* attributesList = nullptr;
	unsigned int attributesListSize = 0;
}VertexBufferDesc;



class VertexArrayObject
{
public:
	VertexArrayObject(const VertexBufferDesc& desc);
	void init(const VertexBufferDesc& desc);
	~VertexArrayObject();
	
	unsigned int getID();
	unsigned int getVertexBufferSize();
	unsigned int getVertexSize();
private:
	unsigned int vertexBufferID;
	unsigned int vertexArrayObjectID;
	VertexBufferDesc vertexBufferData;
};


//typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
