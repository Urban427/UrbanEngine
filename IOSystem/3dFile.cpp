#include "IOSystem.h"
#include <stdio.h>
#include "VertexDictionary.h"

//files
Mesh IOSystem::readFBX(const char* filename)
{
	CFile f = openCFile(filename);;
	if(f.isEmpty()) {
		return Mesh();
	}
	
	FBXfile fbxFile(f);
	
	
	
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
		
		
		TriangulatePolygon(result_vertexes, normals[i - 1], vector_array, removed_vertexes, indicies_array + first, number_of_points, result_indices + real_first);
		
		
		real_first += number_of_points * 3 - 6; 
		first = i;
	}
	delete[] removed_vertexes;
	delete[] helping_indicies;
	delete[] vector_array;
	delete[] Vertexes;
	delete[] normals;
	delete[] uv_vertexes;
	
	return {result_indices, real_number_of_indicies, result_vertexes, dictionary.getNumberOfElements(), nullptr, 0};
}