#include "AndroidFilter.h"
#include <sys/time.h>

AndroidFilter::AndroidFilter()
{
	
}

AndroidFilter::~AndroidFilter()
{
	
}

void AndroidFilter::setSize(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
}

Rect AndroidFilter::getInnerSize()
{
	return Rect(width, height);
}

char AndroidFilter::init()
{
	return 0;
}

char AndroidFilter::broadcast()
{
	return 0;
}


double AndroidFilter::getTime()
{
	struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_usec / 1000000;
}