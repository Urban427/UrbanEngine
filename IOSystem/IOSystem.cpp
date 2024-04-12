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
	return 0.5f * (a.x * ((double) c.y - b.y) + b.x * ((double) a.y - c.y) + c.x * ((double) b.y - a.y)) > 0;
}

bool inTrinagle(Vector2 a, Vector2  b, Vector2 c, Vector2 checkPoint)
{
	  float denominator = (b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y);

        if (denominator == 0)
            return true;
        denominator = 1.0f / denominator;
        float alpha = denominator * ((b.y - c.y) * (checkPoint.x - c.x) + (c.x - b.x) * (checkPoint.y - c.y));
        float beta  = denominator * ((c.y - a.y) * (checkPoint.x - c.x) + (a.x - c.x) * (checkPoint.y - c.y));
        float gamma = 1.0f - alpha - beta;

        return !(alpha < 0 || beta < 0 || gamma < 0);
}

#include <stdio.h>
void TriangulatePolygon(Vector3* vertex_array, Vector3 normal, bool* removed_vertexes, int* index_array, int number_of_points, int* result_indices)
{
	switch(number_of_points)
	{
		case(3):
		{
			*(result_indices++) = *(index_array++);
			*(result_indices++) = *(index_array++);
			*result_indices = *index_array;
			return;
		}
	}
	
	
	Vector3 summ = normal;
	if(summ.x < 0) { summ.x = -summ.x; }
	if(summ.y < 0) { summ.y = -summ.y; }
	if(summ.z < 0) { summ.z = -summ.z; }
	
	
	int ia = 0;
	int ib = 1;
	float ic = normal.z;
	if(summ.x > summ.y)
	{
		if(summ.x > summ.z)
		{
			ia = 1;
			ib = 2;
			ic = normal.x;
		}
	}
	else if(summ.y > summ.z)
	{
		ia = 2;
		ib = 0;
		ic = normal.y;
	}
	if(ic > 0)
	{
		int tmp = ia;
		ia = ib;
		ib = tmp;
	}
	
	Vector2* points = new Vector2[number_of_points];
	Vector2* points_ptr = points;
	for(int i = 0; i < number_of_points; i++)
	{
		points_ptr->x = vertex_array[index_array[i]][ia];
		points_ptr->y = vertex_array[index_array[i]][ib];
		points_ptr++;
		//printf("%d) ", index_array[i]);
		//printf("%f %f %f\n", vertex_array[index_array[i]][0], vertex_array[index_array[i]][1], vertex_array[index_array[i]][2]);
	}
	
	int number_of_unused_points = number_of_points;
	int next = 0;
	int prev = number_of_points - 1;
	int ear;
	int numFound = 0;
	while(number_of_unused_points >= 3)
	{
		numFound = 0;
		for(ear = next;; prev = ear, ear = next)
		{
			//find next point
			for(next = ear + 1; removed_vertexes[(next >= number_of_points ? next = 0 : next)]; next++);
			if (next < ear)
				if (++numFound == 2)
					break;
			
			
			
			Vector2 a = points[prev], b = points[ear], c = points[next];
			if(clockwiseTrio(a, b, c) == 0)
			{
				//printf("clockwiseTrio\n", prev, ear, next);
				continue;
			}
			
			int j = 0;
			for(; j < number_of_points; j++)
			{
				if(j == ear || j == prev || j == next)
				{
					continue;
				}
				if(inTrinagle(a, b, c, points[j]))
				{
					break;
				}
			}
			if(j != number_of_points)
			{
				continue;
			}
			
			
			break;
		}
		
		
		*(result_indices++) = index_array[prev];
		*(result_indices++) = index_array[ear];
		*(result_indices++) = index_array[next];
		//printf("checked: %d %d %d\n", prev, ear, next);
		removed_vertexes[ear] = 1;
		number_of_unused_points--;
		
	}
	int i = 0;
	for(; i < number_of_points; i++) {
		if(removed_vertexes[i] == 0) {
			//*(result_indices++) = index_array[i++];
			break;
		}
	}
	for(; i < number_of_points; i++) {
		if(removed_vertexes[i] == 0) {
			//*(result_indices++) = index_array[i++];
			break;
		}
	}
	for(; i < number_of_points; i++) {
		if(removed_vertexes[i] == 0) {
			//*(result_indices++) = index_array[i++];
			break;
		}
	}
	//printf("checked: %d %d %d\n", prev, ear, next);

}



//files
Mesh IOSystem::readFBX(const char* filename)
{
	CFile file = readFile(filename);
	if(file.pointer == nullptr) {
		return Mesh();
	}
	FBXfile fbxFile(file);
	delete[] file.start;
	
	
	
	Node* Objects 		= fbxFile.findChildrenByName("Objects",  fbxFile.getRoot());
	Node* Geometry 		= fbxFile.findChildrenByName("Geometry", Objects);
	Node* Vertices 		= fbxFile.findChildrenByName("Vertices", Geometry);
	Node* Indecies 		= fbxFile.findChildrenByName("PolygonVertexIndex", Geometry);
	Node* LayerNormal 	= fbxFile.findChildrenByName("LayerElementNormal", Geometry);
	Node* Normals	 	= fbxFile.findChildrenByName("Normals", LayerNormal);
	Node* LayerUV 		= fbxFile.findChildrenByName("LayerElementUV", Geometry);
	Node* UV 			= fbxFile.findChildrenByName("UV", LayerUV);
	Node* UVIndex 		= fbxFile.findChildrenByName("UVIndex", LayerUV);
	
	
	printf("%s\n", fbxFile.findChildrenByName("MappingInformationType", LayerNormal)->props[0].rawData);
	for(int i = 0; i < LayerNormal->children.size(); i++)
	{
		printf("%s\n", LayerNormal->children[i]->name);
	}
	
	
	//uv
	int number_of_uv_indexes = UVIndex->props[0].ArrayLength;
	int* uv_indexes = UVIndex->props[0].IntegerArray;
	for(int i = 0; i < number_of_uv_indexes; i++)
	{
		printf("%d ", uv_indexes[i]);
	}
	
	int number_of_uv_vertexes = UV->props[0].ArrayLength / 2;
	Vector2* uv_vertexes = new Vector2[number_of_uv_vertexes];
	for(int i = 0, j = 0; i < UV->props[0].ArrayLength; i+=2, j++)
	{
		uv_vertexes[j] = Vector2(UV->props[0].DoubleArray[i], UV->props[0].DoubleArray[i + 1]);
		printf("%f %f\n", uv_vertexes[j].x, uv_vertexes[j].y);
	}
	
	
	//normals
	int normals_length = Normals->props[0].ArrayLength;
	Vector3* normals = new Vector3[normals_length / 3];
	for(int i = 0, j=0; i < normals_length; i += 3, j++)
	{
		normals[j] = Vector3(Normals->props[0].DoubleArray[i], Normals->props[0].DoubleArray[i + 2], Normals->props[0].DoubleArray[i + 1]); 
		///printf("%d)%f %f %f\n", j, normals[j].x, normals[j].y, normals[j].z);
	}
	
	
	//vertexes
	int  number_of_vertexes = Vertices->props[0].ArrayLength / 3;
	Vector3* Vertexes = new Vector3[number_of_vertexes];
	for(int i = 0, j = 0; i < Vertices->props[0].ArrayLength; i += 3, j++)
	{
		Vertexes[j] = Vector3(Vertices->props[0].DoubleArray[i], Vertices->props[0].DoubleArray[i + 2], Vertices->props[0].DoubleArray[i + 1]);
	}
	
	//indexes
	int* indicies_array = Indecies->props[0].IntegerArray;
	int  number_of_indicies = Indecies->props[0].ArrayLength;
	
	
	//count real number of indecies for trinagles
	bool* removed_vertexes  = new bool[number_of_vertexes];
	
	
	printf("number of indecies = %d\n", number_of_indicies);
	printf("number of points = %d\n", number_of_vertexes);
	printf("number of normals  = %d\n", normals_length / 3);
	
	
	printf("number of uv index = %d\n", normals_length / 3);
	printf("number of uv points= %d\n", normals_length / 3);
	
	
	//printf("\n");for(int i = 0; i < number_of_vertexes; i++) 	{ printf("%d) %f %f %f\n", i, Vertexes[i].x, Vertexes[i].y, Vertexes[i].z); } printf("\n");
	//printf("\n");for(int i = 0; i < number_of_indicies; i++) 	{ printf("%d ", indicies_array[i]); } printf("\n");
	
	int real_first = 0;
	int first = 0;
	int number_of_points;
	int real_number_of_indicies = 0;
	
	
	int number_of_duplicated_vertexes = 0;
	int** duplicates = new int*[number_of_vertexes];
	memset(duplicates, 0, number_of_vertexes * sizeof(void*));
	
	
	for(int i = 0; i < number_of_indicies; i++)
	{
		int index = indicies_array[i];
		if(index < 0) {
			index = -(index + 1);
		}
		printf("%d) index: %d, duplcates: %d\n", i, index, duplicates[index]);
		if(duplicates[index] == nullptr)
		{
			duplicates[index] = new int[5];
			duplicates[index][0] = uv_indexes[i];
			number_of_duplicated_vertexes++;
		}
		else
		{
			
		}
		
		//check the end of the polygon
		if(!(indicies_array[i] & 0x80'00'00'00)) {
			continue;
		}
		
		//get the number of points
		number_of_points = i - first + 1;
		if(number_of_points < 3) {first = i + 1; continue;}
		real_number_of_indicies += number_of_points * 3 - 6;
		first = i + 1;
	}
	//printf("number of indicies = %d\n\n", real_number_of_indicies);
	printf("number of read vertexes = %d\n", number_of_duplicated_vertexes);
	
	
	int* result_indices = new int[real_number_of_indicies];
	memset(result_indices, 0, real_number_of_indicies * 4);
	//printf("\n");for(int i = 0; i < real_number_of_indicies; i++) 	{ printf("%d ", result_indices[i]); } printf("\n");
	first = 0;
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
		number_of_points = i - first;
		if(number_of_points < 3) {first = i; continue;}
		memset(removed_vertexes, 0, number_of_points);
		
		
		TriangulatePolygon(Vertexes, normals[i - 1], removed_vertexes, indicies_array + first, number_of_points, result_indices + real_first);
		
		
		//for(int j = first; j < i; j++) { printf("%i ", indicies_array[j]); } printf("\n");
		real_first += number_of_points * 3 - 6; 
		first = i;
	}
	delete[] removed_vertexes;
	
	
	printf("number of trinagles: %d\n", real_number_of_indicies / 3);
	//printf("\n");for(int i = 0; i < real_number_of_indicies; i++) 	{ printf("%d ", result_indices[i]); } printf("\n");
	
	Mesh res;
	res.index = result_indices;
	res.index_size = real_number_of_indicies;
	res.vertex = Vertexes;
	res.vertex_size = number_of_vertexes;
	
	
	return res;
}