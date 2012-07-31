#ifndef RANDOM_HPP
#define RANODM_HPP

#include "Common.h"

#include "Mersenne/randomc.h" //mersenne

class Random
{
public:
	Random();

	real NextReal();
	bit NextBit();
	bit NextBit(real probability); // probability of returning 1

	void Randomize(void* buf, int size);

private:
	CRandomMersenne mersenne;
};

extern Random rnd;

#endif
