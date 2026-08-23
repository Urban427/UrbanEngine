#include "FileSystem.h"

//input




//files
CFile::CFile(){}

CFile::CFile(char* ptr, int size) {
	start = ptr;
	pointer = ptr;
	_size = size;
}

CFile::CFile(CFile&& other) noexcept : start(other.start), pointer(other.pointer), _size(other._size), capacity(other.capacity) {
    other.start = nullptr;
    other.pointer = nullptr;
    other._size = 0;
    other.capacity = 0;
}

CFile& CFile::operator=(CFile&& other) noexcept {
    if (this != &other) {
        delete[] start;

        start = other.start;
        pointer = other.pointer;
        _size = other._size;
        capacity = other.capacity;

        other.start = nullptr;
        other.pointer = nullptr;
        other._size = 0;
        other.capacity = 0;
    }
    return *this;
}

CFile::~CFile() {
	delete[] start;
}

char readCFile(void* value, int value_size, CFile& file)
{
	memcpy(value, file.pointer, value_size);
	file.pointer += value_size;
	return 0;
}

void seekCFile(CFile& file, int offset, int origin) {
	switch(origin) {
		case(SEEK_SET): {
			if(offset < 0)
			{
				offset = 0;
			}
			file.pointer = file.start + offset;
			return;
		}

		case(SEEK_END): {
			file.pointer = file.start + file._size + offset;
			return;
		}

		case(SEEK_CUR): {
			file.pointer += offset;
			return;
		}
	}
}

CFile createCFile() { 
	CFile file;
    file.capacity = 256;
    file._size = 0;
    file.start = new char[file.capacity];
    file.pointer = file.start;
    return file;
}

void writeCFile(const void* data, int size, CFile& file){
	unsigned int used = file.pointer - file.start;
    if (used + size > file.capacity) {
        unsigned int newCapacity = file.capacity;
        while (used + size > newCapacity) newCapacity <<= 1;

        char* newBuffer = new char[newCapacity];
        memcpy(newBuffer, file.start, used);
        delete[] file.start;

        file.start = newBuffer;
        file.pointer = newBuffer + used;
        file.capacity = newCapacity;
    }

    memcpy(file.pointer, data, size);
    file.pointer += size;

    unsigned int written = file.pointer - file.start;
    if (written > file._size) file._size = written;
}