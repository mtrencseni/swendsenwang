#include "Timer.hpp"

Timer::Timer()
{
	elapsed = 0;
}

void Timer::Start()
{
	start = GetTickCount();
}

void Timer::End()
{
	elapsed += GetTickCount() - start;
}

TimeSpan Timer::Elapsed()
{
	return TimeSpan(elapsed);
}

void Timer::Report(char* text)
{
	(Elapsed()).Report(text);
}
