#ifndef TIMER_H
#define TIMER_H

#include "windows.h"
#include "TimeSpan.hpp"

class Timer
{
public:
	Timer();

	void Start();
	void End();

	TimeSpan Elapsed();
	
	void Report(char* text);

private:
	long start;
	long elapsed;
};

#endif