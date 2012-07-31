#include "Swendsen.hpp"
#include "Random.hpp"
#include <math.h>
#include <stdio.h>

Swendsen::Swendsen(int length)
: sites(length), xbonds(length), ybonds(length), zbonds(length), memberships(length),
randBits(length * length * length), clusters(length * length * length)
{
	this->length = length;

	int size = length * length * length;
}

Swendsen::~Swendsen()
{
}

void Swendsen::Init(real beta, real J)
{
	this->beta = beta;
	this->J = J;
	this->bondprob = BondProb(beta);

	sites.Randomize();
}

void Swendsen::Step()
{
	RandomizeBonds();

	Cluster();

	FlipClusters();
}

real Swendsen::Magnetization()
{
	int		x, y, z;
	real	m;

	m = 0;
	for (x = 0; x < length; x++)
		for (y = 0; y < length; y++)
			for (z = 0; z < length; z++)
				m += sites.Get(x, y, z) ? 1 : -1;

	m /= (length * length * length);

	return m;
}

real Swendsen::BondProb(real beta)
{
	return (1 - exp(-2 * beta * J));

}

/* Generate bonds according to P(bond) = 1 - exp(-2 * beta * J) if the two spin neighbours are the same */
void Swendsen::RandomizeBonds()
{
	int		x, y, z;

	for (x = 0; x < length; x++)
	{
		for (y = 0; y < length; y++)
		{
			for (z = 0; z < length; z++)
			{
				if (sites.Get(x, y, z) == sites.Get(x + 1, y, z))
					xbonds.Set(x, y, z, rnd.NextBit(bondprob));
				else
					xbonds.Set(x, y, z, 0);

				if (sites.Get(x, y, z) == sites.Get(x, y + 1, z))
					ybonds.Set(x, y, z, rnd.NextBit(bondprob));
				else
					ybonds.Set(x, y, z, 0);

				if (sites.Get(x, y, z) == sites.Get(x, y, z + 1))
					zbonds.Set(x, y, z, rnd.NextBit(bondprob));
				else
					zbonds.Set(x, y, z, 0);
			}
		}
	}
}

/* Find clusters in bond lattice */
void Swendsen::Cluster()
{
	int		x, y, z, m, mx, my, mz, size;
	bit		bx, by, bz;

	size = length * length * length;
	for (int i = 0; i < size; i++)
		clusters.Set(i, i);

	nClusters = 0;
	
	x = y = z = 0;
	m = nClusters++;
	memberships.Set(x, y, z, m);

	for (z = 1; z < length; z++)
	{
		bz = zbonds.Get(x, y, z);
		mz = memberships.Get(x, y, z - 1);

		if (bz)
			m = mz;
		else
			m = nClusters++;
		memberships.Set(x, y, z, m);
	}

	for (y = 1; y < length; y++)
			for (z = 0; z < length; z++)
			{
				by = ybonds.Get(x, y, z);
				bz = zbonds.Get(x, y, z);
				my = memberships.Get(x, y - 1, z);
				mz = memberships.Get(x, y, z - 1);

				if (z == 0)
				{
					if (by)
						m = my;
					else
						m = nClusters++;
					memberships.Set(x, y, z, m);
					continue;
				}

				if (by && bz) {
					if (my < mz)
					{
						m = my;
						LinkCluster(mz, m);
					} else {
						m = mz;
						LinkCluster(my, m);
					}
				} else if (by && !bz) {
					m = my;
				} else if (!by && bz) {
					m = mz;
				} else {
					m = nClusters++;
				}
				memberships.Set(x, y, z, m);
			}

	for (x = 1; x < length; x++)
	{
		y = z = 0;
		bx = xbonds.Get(x, y, z);
		mx = memberships.Get(x - 1, y, z);
		if (bx)
			m = mx;
		else
			m =  nClusters++;
		memberships.Set(x, y, z, m);

		for (z = 1; z < length; z++)
		{
			bx = xbonds.Get(x, y, z);
			bz = zbonds.Get(x, y, z);
			mx = memberships.Get(x - 1, y, z);
			mz = memberships.Get(x, y, z - 1);

			if (bx && bz) {
				if (mx < mz)
				{
					m = mx;
					LinkCluster(mz, m);
				} else {
					m = mz;
					LinkCluster(mx, m);
				}
			} else if (bx && !bz) {
				m = mx;
			} else if (!bx && bz) {
				m = mz;
			} else {
				m = nClusters++;
			}
			memberships.Set(x, y, z, m);
		}

		for (y = 1; y < length; y++)
		{
			for (z = 0; z < length; z++)
			{
				bx = xbonds.Get(x, y, z);
				by = ybonds.Get(x, y, z);
				bz = zbonds.Get(x, y, z);
				mx = memberships.Get(x - 1, y, z);
				my = memberships.Get(x, y - 1, z);
				mz = memberships.Get(x, y, z - 1);

				if (z == 0)
				{
					if (bx && by) {
						if (mx < my)
						{
							m = mx;
							LinkCluster(my, m);
						} else {
							m = my;
							LinkCluster(mx, m);
						}
					} else if (bx && !by) {
						m = mx;
					} else if (!bx && by) {
						m = my;
					} else {
						m = nClusters++;
					}
					memberships.Set(x, y, z, m);
					continue;
				}
				
				if (bx && by && bz) {
					if (mx <= my && mx <= mz) {
						m = mx;
						LinkCluster(my, m);
						LinkCluster(mz, m);
					} else if (my <= mx && my <= mz) {
						m = my;
						LinkCluster(mx, m);
						LinkCluster(mz, m);
					} else {
						m = mz;
						LinkCluster(mx, m);
						LinkCluster(my, m);
					}
				} else if (bx && by && !bz) {
					if (mx < my)
					{
						m = mx;
						LinkCluster(my, m);
					} else {
						m = my;
						LinkCluster(mx, m);
					}
				} else if (bx && !by && bz) {
					if (mx < mz) {
						m = mx;
						LinkCluster(mz, m);
					} else {
						m = mz;
						LinkCluster(mx, m);
					}
				} else if (bx && !by && !bz) {
					m = mx;
				} else if (!bx && by && bz) {
					if (my < mz) {
						m = my;
						LinkCluster(mz, m);
					} else {
						m = mz;
						LinkCluster(my, m);
					}
				} else if (!bx && by && !bz) {
					m = my;
				} else if (!bx && !by && bz) {
					m = mz;
				} else {
					m = nClusters++;
				}
				memberships.Set(x, y, z, m);
			}
		}
	}
}

/* For each cluster: flip with probability 0.5 */
void Swendsen::FlipClusters()
{
	int		i, x, y, z;

	randBits.Randomize();

	for (i = 0; i < nClusters; i++)
	{
		int tc = TailCluster(i);
		randBits.Set(i, randBits.Get(tc));
	}

	for (x = 0; x < length; x++)
		for (y = 0; y < length; y++)
			for (z = 0; z < length; z++)
				sites.Set(x, y, z, randBits.Get(memberships.Get(x, y, z)));
}

/* src and dst are now the same clusters, put them on the same chain */
void Swendsen::LinkCluster(int src, int dst)
{
	if (src == dst)
		return;

	if (clusters.Get(src) == src) {
		clusters.Set(src, dst);
	} else {
		if (dst < clusters.Get(src))
			LinkCluster(clusters.Get(src), dst);
		else
			LinkCluster(dst, clusters.Get(src));
	}
}

/* Find the tail cluster on the chain */
int Swendsen::TailCluster(int c)
{
	if (clusters.Get(c) == c)
		return c;
	else
		return TailCluster(clusters.Get(c));
}
