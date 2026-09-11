#include "FileSystem.h"
#include <stdio.h>
#include <cstdlib>
#include <sys/stat.h>

CFile openCFile(const char* name)
{
	FILE* f = fopen(name, "rb");
	//end if file not found
	if(f == NULL) {
		return CFile();
	}
	
	//get file size
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f); 
	fseek(f, 0, SEEK_SET);

	//read file
	char* data = nullptr;
	data = static_cast<char*>(malloc(size + 1));
	fread(data, size, 1, f);
	data[size] = '\0';
	fclose(f);
	
	return CFile(data, size + 1);
}

void saveCFile(const char* name, CFile& file) {
    FILE* f = fopen(name, "wb"); 
    if (!f) return;
    fwrite(file.start, 1, file._size, f);
    fclose(f);
}

bool getFileModificationTime(const char* name, time_t& time) {
    struct stat info;
    if (stat(name, &info) != 0) return false;
    time = info.st_mtime;
    return true;
}

bool isFileOlder(const char* file, const char* reference) {
    time_t fileTime;
    time_t referenceTime;
    if (!getFileModificationTime(file, fileTime)) return true;
    if (!getFileModificationTime(reference, referenceTime)) return false;
    return fileTime < referenceTime;
}