#pragma once
#include "gl2.h"

typedef struct {
    int width;
    int height;
    int size;
    GLenum gl_color_format;
    void* data;
} RawImageData;


RawImageData readPng();
RawImageData readBMPFile(const char* filename);