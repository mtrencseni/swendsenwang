#include "../stdafx.h"
#include "Swendsen.hpp"
#include "Timer.hpp"
#include "Random.hpp"
#include <stdio.h>
#include <math.h>

void CheckArgs(int argc, _TCHAR* argv[]);

int _tmain(int argc, _TCHAR* argv[])
{
	int		length, nSteps, step;
	real	betaFrom, betaTo, betaIncr;
	real	beta, J, sum, magnetization;
	FILE*	fp;
	Timer	timer;
	bool	doAbsAvg;

	CheckArgs(argc, argv);

	if (wcscmp(argv[1], _T("absAvg")) == 0)
		doAbsAvg = true;
	else
		doAbsAvg = false;
	length = _wtoi(argv[3]);
	nSteps =_wtoi(argv[4]);
	betaFrom = _wtof(argv[5]);
	betaTo = _wtof(argv[6]);
	betaIncr = _wtof(argv[7]);
	J = _wtof(argv[8]);

	fp = _wfopen(argv[2], _T("w"));

	timer.Start();
	Swendsen sw(length);
	for (beta = betaFrom; beta < betaTo; beta += betaIncr)
	{
		sw.Init(beta, J);
	
		sum = 0.0;
		for (step = 0; step < nSteps; step++) {
			sw.Step();
			if (doAbsAvg)
				sum += fabs(sw.Magnetization());
		}

		if (doAbsAvg)
			magnetization = sum / nSteps;
		else
			magnetization = sw.Magnetization();

		fprintf(fp, "%f, %f\n", beta, magnetization);

		printf("%f / %f, m = %f\n", beta, betaTo, magnetization);
	}
	timer.End();
	timer.Report("Total time");

	fclose(fp);
	
	return 0;
}

void CheckArgs(int argc, _TCHAR* argv[])
{
	if (argc != 9) {
		wprintf(_T("%s <outFile.csv> <absAvg> <length> <nSteps> <betaFrom> <betaTo> <betaIncr> <J>"), argv[0]);
		exit(1);
	}
}