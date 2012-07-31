#include "Random.hpp"
#include "windows.h"

Random rnd; // the singleton

Random::Random()
: mersenne(GetTickCount())
{
}

real Random::NextReal()
{
	return (real) mersenne.Random();
}

bit Random::NextBit()
{
	return NextBit(0.5);
}

bit Random::NextBit(real probability) // probability of returning 1
{
	real r = NextReal();

	if (r < probability)
		return up;
	else
		return down;	
}

void Random::Randomize(void* buf, int bufsize)
{
	uint32	u;
	uint32*	ptr;
	char*	cp;
	int		i, n, m;

	ptr = (uint32*) buf;
	n = bufsize / sizeof(uint32);

	for (i = 0; i < n; i++)
		ptr[i] = mersenne.BRandom();
	
	m = n * sizeof(uint32);
	if (m < bufsize)
	{
		cp = (char*) buf;
		u = mersenne.BRandom();
		memcpy(&cp[m], &u, bufsize - m);
	}
}