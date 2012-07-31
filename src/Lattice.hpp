#ifndef LATTICE_HPP
#define LATTICE_HPP

#include "Common.h"
#include "Field.hpp"

class BitLattice
{
public:
	BitLattice(int length);
	~BitLattice();

	void Clear();
	void Randomize();

	bit Get(int x, int y, int z);
	void Set(int x, int y, int z, bit b);

private:
	inline int InBound(int x);

	int length;
	int length2;
	BitField bitField;
};

template<class T>
class Lattice
{
public:
	Lattice(int length);
	~Lattice();

	void Clear();
	void Randomize();

	T Get(int x, int y, int z);
	void Set(int x, int y, int z, T t);

private:
	inline int InBound(int x);

	int length;
	int length2;
	Field<T> field;
};

/* Implementation of Lattice<T> */

template<class T>
Lattice<T>::Lattice(int length)
: field(length * length * length)
{
	this->length = length;
	this->length2 = length * length;
}

template<class T>
Lattice<T>::~Lattice()
{
}

template<class T>
void Lattice<T>::Clear()
{
	field.Clear();
}

template<class T>
void Lattice<T>::Randomize()
{
	field.Randomize();
}

template<class T>
T Lattice<T>::Get(int x, int y, int z)
{
	x = InBound(x);
	y = InBound(y);
	z = InBound(z);

	return field.Get(length2 * x + length * y  + z);
}

template<class T>
void Lattice<T>::Set(int x, int y, int z, T t)
{
	x = InBound(x);
	y = InBound(y);
	z = InBound(z);

	field.Set(length2 * x + length * y  + z, t);
}

template<class T>
int Lattice<T>::InBound(int x)
{
	if (x < 0 || x >= length) {
		x = x % length;
		if (x < 0)
			x = length - x;
	}

	return x;
}

#endif
