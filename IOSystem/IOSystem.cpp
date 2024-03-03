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
	for(int i = 0; i < Indecies->props[0].ArrayLength; i++)
	{
		printf("%i\n", Indecies->props[0].IntegerArray[i]);
	}
	
	
	Vector3* Vertexes = new Vector3[Vertices->props[0].ArrayLength / 3];
	for(int i = 0, j = 0; i < Vertices->props[0].ArrayLength; i+=3, j++)
	{
		Vertexes[j] = Vector3(Vertices->props[0].DoubleArray[i], Vertices->props[0].DoubleArray[i + 1], Vertices->props[0].DoubleArray[i + 2]);
		printf("%f %f %f\n", Vertexes[j].x, Vertexes[j].y, Vertexes[j].z);
	}
	system("pause");
	return Vertexes;
}