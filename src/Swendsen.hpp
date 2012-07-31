#ifndef SWENDSEN_HPP
#define SWENDSEN_HPP

#include "Common.h"
#include "Field.hpp"
#include "Lattice.hpp"

class Swendsen
{
public:
	Swendsen(int length);
	~Swendsen();

	void Init(real beta, real J);
	void Step();

	real Magnetization();

private:
	real BondProb(real beta);

	void RandomizeBonds();
	void Cluster();
	void FlipClusters();

	void LinkCluster(int src, int dst);
	int TailCluster(int cluster);

	int length;
	real beta, J;
	real bondprob;
	real magnetization;

	int nClusters;

	BitLattice sites;
	BitLattice xbonds, ybonds, zbonds;
	Lattice<int> memberships;
	Field<int> clusters;
	BitField randBits;
};

#endif
