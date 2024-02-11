#pragma once

template<class T>
class array
{
public:
	array();
	~array();

	unsigned int size();
	void push_back(const T& value);
	T& back();
	T* begin();
	const T* begin() const;
	T* end();
	const T* end() const;
public:
	T& operator[](unsigned int index);
private:
	unsigned int _size;
	T* data;
};

#include "_array.imp"