#include "IOstructures.h"

//input




//files
char readCFile(void* value, int value_size, CFile& file)
{
	memcpy(value, file.pointer, value_size);
	file.pointer += value_size;
	return 0;
}