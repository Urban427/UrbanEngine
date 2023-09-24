#pragma once

struct IndexArrayDesc
{
	unsigned int* indices = nullptr;
	unsigned int size;
};


class IndexArrayObject
{
public:
	IndexArrayObject(const IndexArrayDesc& desc);
	void init(const IndexArrayDesc& desc);
	//~IndexArrayObject();
	
	unsigned int getSize();
	unsigned int getID();
private:
	unsigned int indexBufferID;
	unsigned int size;
};
