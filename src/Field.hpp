#ifndef BITFIELD_HPP
#define BITFIELD_HPP

#include "Common.h"
#include <stdlib.h>

class BitField
{
public:
	BitField(int length);
	~BitField();

	void Clear();
	void Randomize();

	bit Get(int i);
	void Set(int i, bit b);

private:
	int bufsize;
	char* buffer;
};

template<class T>
class Field
{
public:
	Field(int length);
	~Field();

	void Clear();
	void Randomize();

	T Get(int i);
	void Set(int i, T t);

private:
	int bufsize;
	T* buffer;
};

/* Implementation of Field<T> */

template<class T>
Field<T>::Field(int length)
{
	this->bufsize = length * sizeof(T);
	this->buffer = (T*) malloc(bufsize);
}

template<class T>
Field<T>::~Field()
{
	free(buffer);
}

template<class T>
void Field<T>::Clear()
{
	memset(buffer, 0, bufsize);
}

template<class T>
void Field<T>::Randomize()
{
	rnd.Randomize(buffer, bufsize);
}

template<class T>
T Field<T>::Get(int i)
{
	return buffer[i];
}

template<class T>
void Field<T>::Set(int i, T t)
{
	buffer[i] = t;
}


#endif
