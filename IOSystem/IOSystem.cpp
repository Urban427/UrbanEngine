#include "IOSystem.h"
#include "VertexDictionary.h"

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
void TriangulatePolygon(Vertex* vertex_array, Vector3 normal, Vector2* vector2_array, bool* removed_vertexes, int* index_array, int number_of_points, int* result_indices, int start_index)
{
	switch(number_of_points)
	{
		case(2):
		{
			*(result_indices++) = start_index++;
			*(result_indices++) = start_index++;
			*result_indices 	= start_index;
			return;
		}
	}
	
	normal = normal * -1;
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
	
	Vector2* points_ptr = vector2_array;
	for(int i = 0; i < number_of_points; i++)
	{
		points_ptr->x = vertex_array[index_array[i]].pos[ia];
		points_ptr->y = vertex_array[index_array[i]].pos[ib];
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
			
			
			
			Vector2 a = vector2_array[prev], b = vector2_array[ear], c = vector2_array[next];
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
				if(inTrinagle(a, b, c, vector2_array[j]))
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
		
		
		*(result_indices++) = index_array[ prev];
		*(result_indices++) = index_array[ ear ];
		*(result_indices++) = index_array[ next];
		//printf("%d %d %d\n", index_array[ prev], index_array[ ear], index_array[ next]);
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
	//delete[] file.start;
	
	
	
	Node* Objects 		= fbxFile.findChildrenByName("Objects",  fbxFile.getRoot());
	Node* Geometry 		= fbxFile.findChildrenByName("Geometry", Objects);
	Node* Vertices 		= fbxFile.findChildrenByName("Vertices", Geometry);
	Node* Indecies 		= fbxFile.findChildrenByName("PolygonVertexIndex", Geometry);
	Node* LayerNormal 	= fbxFile.findChildrenByName("LayerElementNormal", Geometry);
	Node* Normals	 	= fbxFile.findChildrenByName("Normals", LayerNormal);
	Node* LayerUV 		= fbxFile.findChildrenByName("LayerElementUV", Geometry);
	Node* UV 			= fbxFile.findChildrenByName("UV", LayerUV);
	Node* UVIndex 		= fbxFile.findChildrenByName("UVIndex", LayerUV);
	Node* LayerMaterial = fbxFile.findChildrenByName("LayerElementMaterial", Geometry);
	Node* Materials		= fbxFile.findChildrenByName("Materials", LayerMaterial);
	
	
	//indexes
	int* indicies_array = Indecies->props[0].IntegerArray;
	int  number_of_indicies = Indecies->props[0].ArrayLength;
	
	
	//vertexes
	int  number_of_vertexes = Vertices->props[0].ArrayLength / 3;
	Vector3* Vertexes = new Vector3[number_of_vertexes];
	for(int i = 0, j = 0; i < Vertices->props[0].ArrayLength; i += 3, j++) {
		Vertexes[j] = Vector3(Vertices->props[0].DoubleArray[i], Vertices->props[0].DoubleArray[i + 2], Vertices->props[0].DoubleArray[i + 1]);
	}
	
	//normals
	int normals_length 	= Normals->props[0].ArrayLength / 3;
	Vector3* normals = new Vector3[normals_length];
	for(int i = 0, j = 0; j < normals_length; i += 3, j++) {
		normals[j] = Vector3(Normals->props[0].DoubleArray[i], Normals->props[0].DoubleArray[i + 2], Normals->props[0].DoubleArray[i + 1]); 
	}
	
	//uv
	int number_of_uv_indexes = UVIndex->props[0].ArrayLength;
	int* uv_indexes = UVIndex->props[0].IntegerArray;
	int number_of_uv_vertexes = UV->props[0].ArrayLength / 2;
	Vector2* uv_vertexes = new Vector2[number_of_uv_vertexes];
	for(int i = 0, j = 0; i < UV->props[0].ArrayLength; i+=2, j++) {
		uv_vertexes[j] = Vector2(UV->props[0].DoubleArray[i], UV->props[0].DoubleArray[i + 1]);
	}
	
	
	
	//count real number of indecies for trinagles
	bool* removed_vertexes  = new bool[number_of_vertexes];
	int* helping_indicies = new int[number_of_indicies];
	VertexDictionary<Point> dictionary(number_of_vertexes);
	int real_first = 0;
	int first = 0;
	int number_of_points;
	int real_number_of_indicies = 0;
	int max_number_of_points_per_polygon = 0;
	for(int i = 0; i < number_of_indicies; i++)
	{
		//check the end of the polygon
		if(!(indicies_array[i] & 0x80'00'00'00)) {
			helping_indicies[i] = dictionary.addElement({i, uv_indexes[i], normals[i]}, indicies_array[i]);
			continue;
		}
		helping_indicies[i] = dictionary.addElement({i, uv_indexes[i], normals[i]}, -indicies_array[i] - 1);
		
		//get the number of points
		number_of_points = i - first + 1;
		if(number_of_points < 3) {first = i + 1; continue;}
		if(max_number_of_points_per_polygon < number_of_points) { max_number_of_points_per_polygon = number_of_points;}
		real_number_of_indicies += number_of_points * 3 - 6;
		first = i + 1;
	}
	
	Vertex* result_vertexes = new Vertex[dictionary.getNumberOfElements()];
	Vector2* vector_array = new Vector2[max_number_of_points_per_polygon];
	int* result_indices = new int[real_number_of_indicies];
	first = 0;
	int vertex_index = 0;
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
		
		
		for(int j = first; j < i; j++)
		{
			if(j == helping_indicies[j]) {
				result_vertexes[vertex_index] = {Vertexes[indicies_array[j]], normals[j], uv_vertexes[uv_indexes[j]]};
				indicies_array[j] = vertex_index++;
			}
			else {
				indicies_array[j] = indicies_array[helping_indicies[j]];
			}
		}
		
		
		TriangulatePolygon(result_vertexes, normals[i - 1], vector_array, removed_vertexes, indicies_array + first, number_of_points, result_indices + real_first, 0);
		
		
		real_first += number_of_points * 3 - 6; 
		first = i;
	}
	delete[] removed_vertexes;
	delete[] helping_indicies;
	delete[] vector_array;
	
	return {result_indices, real_number_of_indicies, result_vertexes, dictionary.getNumberOfElements(), nullptr, 0};
}

TextureStruct IOSystem::readBMP(const char* filename)
{
	CFile f = readFile(filename);
	if(f.pointer == nullptr) {
		return TextureStruct();
	}

	short  bfType;
	int    bfSize;
	short  bfReserved1;
	short  bfReserved2;
	int    bfOffBits;
    readCFile(&bfType, sizeof(short), f);
    readCFile(&bfSize, sizeof(int), f);
    readCFile(&bfReserved1, sizeof(short), f);
    readCFile(&bfReserved2, sizeof(short), f);
    readCFile(&bfOffBits, sizeof(int), f);
	
	
	int    biSize;
	int    biWidth;
	int    biHeight;
	short   biPlanes;
	short   biBitCount;
	int    biCompression;
	int    biSizeImage; 
	int    biXPelsPerMeter;
	int    biYPelsPerMeter;
	int    biClrUsed;     
	int    biClrImportant;
	
	readCFile(&biSize, sizeof(int), f);
    readCFile(&biWidth, sizeof(int), f);
    readCFile(&biHeight, sizeof(int), f);
    readCFile(&biPlanes, sizeof(short), f);
    readCFile(&biBitCount, sizeof(short), f);
    readCFile(&biCompression, sizeof(int), f);
    readCFile(&biSizeImage, sizeof(int), f);
    readCFile(&biXPelsPerMeter, sizeof(int), f);
    readCFile(&biYPelsPerMeter, sizeof(int), f);
    readCFile(&biClrUsed, sizeof(int), f);
    readCFile(&biClrImportant, sizeof(int), f);
	
	//move to main data
	seekCFile(f, bfOffBits, SEEK_SET);
	
	//set texture's data
	TextureStruct texture;
	texture.width = biWidth;
	texture.height = biHeight;
    texture.pixels = (int*)malloc(biWidth * biHeight * sizeof(int));
	
	//helping values
	char temp = 0;
	unsigned int index = 0;
	
    for(int y = 0; y < biHeight; y++) 
	{
		// left_bottom_corner index -> left_to_corner index
		//index = (biHeight - y - 1) * biWidth;
		
        for(int x = 0; x < biWidth; x++) 
		{
			int r;
			readCFile(&r, biBitCount / 8, f);
			texture.pixels[index] = r;
			
			//change indexes
			index++;
        }
		
		//skip offset
		seekCFile(f,  (biWidth * (biBitCount / 8)) % 4, SEEK_CUR);
    }
	
	return texture;
}