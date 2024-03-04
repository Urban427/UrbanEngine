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


bool clockwiseTrio(Vector2 a, Vector2  b, Vector2 c)
{
	return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) > 0;
}


#include <stdio.h>
//files
Vector3* IOSystem::readFBX(const char* filename)
{
	CFile file = readFile(filename);
	if(file.pointer == nullptr) {
		return nullptr;
	}
	FBXfile fbxFile(file);
	delete[] file.start;
	
	
	
	Node* Objects 	= fbxFile.findChildrenByName("Objects",  fbxFile.getRoot());
	Node* Geometry 	= fbxFile.findChildrenByName("Geometry", Objects);
	Node* Vertices 	= fbxFile.findChildrenByName("Vertices", Geometry);
	Node* Indecies 	= fbxFile.findChildrenByName("PolygonVertexIndex", Geometry);
	
	int  first = 0;
	std::vector<int> result_indicies_array;
	int* indicies_array = Indecies->props[0].IntegerArray;
	int  number_of_vertexes = Vertices->props[0].ArrayLength;
	int  number_of_indicies = Indecies->props[0].ArrayLength;
	bool* removed_vertexes  = new bool[number_of_vertexes];
	for(int i = 0; i < number_of_indicies; i++)
	{
		if(!(indicies_array[i] & 0x80'00'00'00)) {
			continue;
		}
		
		indicies_array[i]++;
		indicies_array[i] *= -1;
		i++;
		
		
		int number_of_points = i - first;
		printf("number: %d\n", number_of_points);
		
		
		memset(removed_vertexes, 0, i - first);
		while(number_of_points > 3)
		{
			int ear = 0;
			for(; ear < i; ear++)
			{
				if(removed_vertexes[ear] == 1) {
					continue;
				}
				
				
			}
			
			number_of_points--;
		}
		
		
		
		for(int j = first; j < i; j++)
		{
			printf("%i\n", indicies_array[j]);
		}
		printf("\n");
		first = i;
	}
	delete[] removed_vertexes;
	
	
	//while(number_of_vertexes > 3)
	{
		
	}
	
	
	Vector3* Vertexes = new Vector3[Vertices->props[0].ArrayLength / 3];
	for(int i = 0, j = 0; i < Vertices->props[0].ArrayLength; i+=3, j++)
	{
		Vertexes[j] = Vector3(Vertices->props[0].DoubleArray[i], Vertices->props[0].DoubleArray[i + 1], Vertices->props[0].DoubleArray[i + 2]);
		printf("%f %f %f\n", Vertexes[j].x, Vertexes[j].y, Vertexes[j].z);
	}
	//system("pause");
	return Vertexes;
}