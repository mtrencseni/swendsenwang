#include "Field.hpp"
#include "Random.hpp"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define GETBIT(x, pos) ( ((x) & ( 1 << (pos))) > 0 ? 1 : 0 )

#define SETBIT(x, pos, val) ( val > 0 ? ((x) |= (1 << (pos))) : ((x) &= ~(1 << (pos))) )

BitField::BitField(int length)
{
	this->bufsize = (int) ceil((double)length / 8);
	this->buffer = (char*) malloc(bufsize);
}

BitField::~BitField()
{
	free(buffer);
}

void BitField::Clear()
{
	memset(buffer, 0, bufsize);
}

void BitField::Randomize()
{
	rnd.Randomize(buffer, bufsize);
}

bit BitField::Get(int i)
{
	int bytepos, bitpos;

	bytepos = i / 8;
	bitpos = i % 8;

	return GETBIT(buffer[bytepos], bitpos);
}

void BitField::Set(int i, bit b)
{
	int bytepos, bitpos;

	bytepos = i / 8;
	bitpos = i % 8;

	SETBIT(buffer[bytepos], bitpos, b);
}
