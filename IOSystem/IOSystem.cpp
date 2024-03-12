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
void TriangulatePolygon(Vector3* vertex_array, bool* removed_vertexes, int* index_array, int number_of_points)
{
	Vector3 summ;
	for(int i = 0; i < number_of_points; i++)
	{
		summ += vertex_array[index_array[i]];
	}
	
	if(summ.x < 0) { summ.x = -summ.x; }
	if(summ.y < 0) { summ.y = -summ.y; }
	if(summ.z < 0) { summ.z = -summ.z; }
	
	
	int a = 0;
	int b = 1;
	if(summ.x > summ.y)
	{
		if(summ.x > summ.z)
		{
			a = 1;
			b = 2;
		}
	}
	else if(summ.y > summ.z)
	{
		a = 0;
		b = 2;
	}
	
	printf("a: %d\nb: %d\n", a, b);
	
	Vector2* points = new Vector2[number_of_points];
	Vector2* points_ptr = points;
	for(int i = 0; i < number_of_points; i++)
	{
		points_ptr->x = vertex_array[index_array[i]][a];
		points_ptr->y = vertex_array[index_array[i]][b];
		points_ptr++;
		printf("%f %f %f\n", vertex_array[index_array[i]][0], vertex_array[index_array[i]][1], vertex_array[index_array[i]][2]);
	}
	
	int* result_indicies_array = new int[number_of_points * 3 - 6];
	int next = 0;
	while(number_of_points > 3)
	{
		int ear = next;
		int prev = 0;
		for(;; prev = ear, ear = next)
		{
			//check if we haven't removed this ear
			//if(removed_vertexes[ear] == 1) {
			//	continue;
			//}
			//find next point
			//for(next = ear + 1; removed_vertexes[next < number_of_points? next : next = 0] == 0; next++);
			
			break;
		}
		
		number_of_points--;
	}
	
	return;
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
	
	
	Vector3* Vertexes = new Vector3[Vertices->props[0].ArrayLength / 3];
	for(int i = 0, j = 0; i < Vertices->props[0].ArrayLength; i+=3, j++)
	{
		Vertexes[j] = Vector3(Vertices->props[0].DoubleArray[i], Vertices->props[0].DoubleArray[i + 1], Vertices->props[0].DoubleArray[i + 2]);
	}
	
	int  first = 0;
	int* indicies_array = Indecies->props[0].IntegerArray;
	int  number_of_vertexes = Vertices->props[0].ArrayLength;
	int  number_of_indicies = Indecies->props[0].ArrayLength;
	bool* removed_vertexes  = new bool[number_of_vertexes];
	for(int i = 0; i < number_of_indicies; i++)
	{
		//check the end of the polygon
		if(!(indicies_array[i] & 0x80'00'00'00)) {
			continue;
		}
		
		//prepare data
		indicies_array[i]++;
		indicies_array[i] *= -1;
		i++;
		
		//get the number of points
		int number_of_points = i - first;
		memset(removed_vertexes, 0, number_of_points);
		
		
		TriangulatePolygon(Vertexes, removed_vertexes, indicies_array + first, number_of_points);
		
		
		for(int j = first; j < i; j++) { printf("%i ", indicies_array[j]); } printf("\n");
		first = i;
	}
	delete[] removed_vertexes;
	
	
	
	
	return Vertexes;
}