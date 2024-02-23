#include "winFileManager.h"
#include <stdio.h>
#include <cstdlib>

char* FileManager::readFile(const char* name)
{
	char* data = nullptr;
	FILE* f = fopen(name, "rb");
	if(f == NULL)
	{
		return nullptr;
	}
	
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f); 
	fseek(f, 0, SEEK_SET);
	
	data = static_cast<char*>(malloc(size + 1));
	fread(data, size, 1, f);
	data[size] = '\0';
	fclose(f);
	return data;
}