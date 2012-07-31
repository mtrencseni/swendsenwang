#include "Lattice.hpp"
#include "Random.hpp"
#include <stdlib.h>
#include <string.h>
#include <math.h>

BitLattice::BitLattice(int length)
: bitField(length * length * length)
{
	this->length = length;
	this->length2 = length * length;
}

BitLattice::~BitLattice()
{
}

void BitLattice::Clear()
{
	bitField.Clear();
}

void BitLattice::Randomize()
{
	bitField.Randomize();
}

bit BitLattice::Get(int x, int y, int z)
{
	x = InBound(x);
	y = InBound(y);
	z = InBound(z);
	
	return bitField.Get(length2 * x + length * y  + z);
}

void BitLattice::Set(int x, int y, int z, bit b)
{
	x = InBound(x);
	y = InBound(y);
	z = InBound(z);

	bitField.Set(length2 * x + length * y  + z, b);
}

int BitLattice::InBound(int x)
{
	if (x < 0 || x >= length) {
		x = x % length;
		if (x < 0)
			x = length - x;
	}

	return x;
}
