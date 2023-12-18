#include "AndroidFilter.h"
#include <sys/time.h>

AndroidFilter::AndroidFilter()
{
	
}

//AndroidFilter::~AndroidFilter(){}

void AndroidFilter::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

Rect AndroidFilter::getInnerSize()
{
	return Rect(width, height);
}

Rect AndroidFilter::getCenter()
{
	return Rect(centerX, centerY);
}

char AndroidFilter::init()
{
	return 0;
}

char AndroidFilter::broadcast()
{
	return 0;
}


void AndroidFilter::initTime()
{
	
}

double AndroidFilter::getDeltaTime()
{
	struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_usec / 1000000;
}