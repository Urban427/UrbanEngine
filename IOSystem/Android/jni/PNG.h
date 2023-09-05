#pragma once
#include "gl2.h"

typedef struct {
    int width;
    int height;
    int size;
    GLenum gl_color_format;
    int* data;
} RawImageData;


RawImageData readResource(const char* filename);