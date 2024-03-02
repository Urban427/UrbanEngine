#include "IOSystem.h"

IOSystem::IOSystem() { }
//IOSystem::~IOSystem() { }


//main
void IOSystem::onCreate(const char* windowName, int width, int height, bool fullscreen)
{
    _Window::init(windowName, width, height, fullscreen);
    _Input::create();
}

void IOSystem::onUpdate()
{
    _Window::broadcast();
    _Input::update();
}



//time
void IOSystem::initTime() {	}
double IOSystem::getDeltaTime(){return 0;}



//window
void IOSystem::setCenterCursorPos()
{
	Rect rect = _Window::getCenter();
	_Input::setCursorPos(rect.width, rect.height);
}





#include <stdio.h>
#include <vector>
#include <zlib.h>



bool Check2Strings(char* a, char* b)
{
	while(1)
	{
		if(*a != *b)
		{
			return false;
		}
		if(*a == 0)
		{
			break;
		}
		a++;
		b++;
	}
	return true;
}

char readCFile(void* value, int value_size, CFile& file)
{
	memcpy(value, file.pointer, value_size);
	file.pointer += value_size;
	return 0;
}

struct AllProps
{
	int Integer;
	float Float;
	double Double;
	char Byte;
	short  Short;
	long Long;
	char* rawData;
	
	int* IntegerArray;
	float* FloatArray;
	double* DoubleArray;
	char* ByteArray;
	short*  ShortArray;
	long* LongArray;
};

struct Node
{
	int EndOffset;
	int numProperties;
	int propertyListLen;
	char listName;
	
	char* name;
	std::vector<Node*> children;
	
};



void getProperties(char type, CFile& file)
{
	switch(type)
	{
		case('C'):
		{
			char lol;
			readCFile(&lol, sizeof(char), file);
			printf("%c\n", lol);
			return;
		}
		case('Y'):
		{
			short lol;
			readCFile(&lol, sizeof(short), file);
			printf("%d\n", lol);
			return;
		}
		case('I'):
		{
			int lol;
			readCFile(&lol, sizeof(int), file);
			printf("%d\n", lol);
			return;
		}
		case('F'):
		{
			int lol;
			readCFile(&lol, sizeof(int), file);
			printf("%f\n", lol);
			return;
		}
		case('D'):
		{
			double lol;
			readCFile(&lol, sizeof(double), file);
			printf("%f\n", lol);
			return;
		}
		case('L'):
		{
			long lol;
			readCFile(&lol, 8, file);
			printf("%ld\n", lol);
			return;
		}
		case('R'):
		{
			
		}
		case('S'):
		{
			char* string;
			int stringLength;
			readCFile(&stringLength, sizeof(int), file);
			string = new char[stringLength];
			readCFile(string, stringLength, file);
			
			for(int i = 0; i < stringLength; i++)
			{
				printf("%c", string[i]);
			}
			printf("\n");
			return;
		}
		case('f'):
		{
			return;
		}
		case('d'):
		{
			int typeSize = 8;
			int ArrayLength = 0;
			int Encoding = 0;
			int CompressedLength = 0;
			readCFile(&ArrayLength, 4, file);
			readCFile(&Encoding, 4, file);
			readCFile(&CompressedLength, 4, file);
			
			unsigned char* array = new unsigned char[ArrayLength * typeSize];
			if(Encoding == 0)
			{
				readCFile(array, ArrayLength * typeSize, file);
				return;
			}
			
			
			long unsigned int lLength = ArrayLength * typeSize;
			unsigned char* compressArray = new unsigned char[CompressedLength];
			readCFile(compressArray, CompressedLength, file);
			int res = uncompress(array, &lLength, compressArray, CompressedLength);
			
			
			double* ar = (double*)array;
			for(int i = 0; i < ArrayLength; i++)
			{
				if(i % 3 == 0)
				{
					printf("   ");
				}
				printf("%f ", ar[i]);
			}
			system("pause");
		}
		case('l'):
		{
			return;
		}
		case('i'):
		{
			int ArrayLength = 0;
			int Encoding = 0;
			int CompressedLength = 0;
			readCFile(&ArrayLength, 4, file);
			readCFile(&Encoding, 4, file);
			readCFile(&CompressedLength, 4, file);
			
			unsigned char* array = new unsigned char[ArrayLength * 4];
			if(Encoding == 0)
			{
				readCFile(array, ArrayLength * 4, file);
				return;
			}
			
			unsigned char* compressArray = new unsigned char[CompressedLength];
			uncompress(array, (long unsigned int*)&ArrayLength, compressArray, CompressedLength);
			
			int* ar = (int*)array;
			for(int i = 0; i < ArrayLength; i++)
			{
				printf("%d ", ar[i]);
			}
			system("pause");
		}
		case('b'):
		{
			return;
		}
	}
}


int readFBXNode(CFile& file, int offset, Node* parent)
{
	if(file.pointer < file.start + offset)
	{
		file.pointer = file.start + offset;
	}
	
	
	
	
	int bytesRead = 13;
	
	
	//read head
	int EndOffset;
	int numProperties;
	int propertyListLen;
	char listName;
	readCFile(&EndOffset, sizeof(int), file);
	readCFile(&numProperties, sizeof(int), file);
	readCFile(&propertyListLen, sizeof(int), file);
	readCFile(&listName, sizeof(char), file);
	parent->EndOffset = EndOffset;
	parent->numProperties = numProperties;
	parent->propertyListLen = propertyListLen;
	parent->listName = listName;
	parent->name = new char[listName];
	readCFile(parent->name, listName, file);
	bytesRead += listName;
	
	
	//printf("startOffset = %d\nEndOffset = %d\nnumProperties = %d\npropertyListLen = %d\nlistNameSize = %d\n", offset, EndOffset, numProperties, propertyListLen, listName);
	for(int i = 0; i < listName; i++) { printf("%c", parent->name[i]); } printf("\n");
	
	
	
	//read properrties
	for(int i = 0; i < numProperties; i++)
	{
		char type = 0;
		readCFile(&type, 1, file);
		printf("%c  ", type);
		getProperties(type, file);
	}
	bytesRead += propertyListLen;
	printf("\n");
	
	
	if(Check2Strings(parent->name, (char*)"Objects"))
	{
		system("pause");
	}
	
	//read children
	while(bytesRead + offset < EndOffset)
	{
		Node* child = new Node();
		bytesRead += readFBXNode(file, offset + bytesRead, child);
		if(child->EndOffset == 0) {break;}
		parent->children.push_back(child);
		//printf("here");
	}
	
	
	return bytesRead;
}




void IOSystem::readFBX(const char* filename)
{
	CFile file = readFile(filename);
	if(file.pointer == nullptr)
	{
		return;
	}
	
	
	//head
	char Kaydara_FBX_Binary[22] = { 0 };
	readCFile(Kaydara_FBX_Binary, 21, file);
	
	char unknownByte1;
	char unknownByte2;
	readCFile(&unknownByte1, 1, file);
	readCFile(&unknownByte2, 1, file);
	
	int version = 0;
	readCFile(&version, 4, file);
	printf("version: %d\n\n", version);
	
	int offset = 27;
	
	Node root;
	do
	{
		Node* node = new Node();
		offset += readFBXNode(file, offset, node);
		if(node->EndOffset == 0) {break;}
		root.children.push_back(node);
	}
	while(1);
	
	printf("end\n");
	
	delete[] file.start;
	return;
}