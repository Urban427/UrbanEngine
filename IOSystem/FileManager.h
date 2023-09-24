#pragma once

#ifdef android
	#include "AndroidFileManager.h"
	#define FileData File
	#define readFile read
	#define openFile(x) open(#x, "rb")
	#define seekFile seek
	#define closeFile close
#elif windows
	#include <stdio.h>
	#define FileData FILE
	#define readFile fread
	#define openFile(x) fopen("../Assets/" #x , "rb")
	#define seekFile fseek
	#define closeFile fclose
#endif