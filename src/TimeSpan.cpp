#include "TimeSpan.hpp"
#include <stdio.h>

TimeSpan::TimeSpan():
	Milliseconds(0),
	Seconds(0),
	Minutes(0),
	Hours(0),
	TotalMilliseconds(0),
	TotalSeconds(0),
	TotalMinutes(0)
{}

TimeSpan::TimeSpan(long start, long end)
{
	*this = TimeSpan(end - start);
}

TimeSpan::TimeSpan(long totalMilliseconds)
{
	TotalMilliseconds = totalMilliseconds;
	TotalSeconds = TotalMilliseconds / 1000;
	TotalMinutes = TotalSeconds / 60;
	Hours = (short) TotalMinutes / 60;
	Minutes = (short) TotalMinutes - Hours * 60;
	Seconds = (short) (TotalSeconds - TotalMinutes * 60);
	Milliseconds = (short) (TotalMilliseconds - TotalSeconds * 1000);
}

TimeSpan TimeSpan::operator+=(TimeSpan other)
{
	*this = TimeSpan(TotalMilliseconds + other.TotalMilliseconds);
	return *this;
}

void TimeSpan::Report(char* text)
{
	printf("%s: %dh%dm%ds%dms\n", text, Hours, Minutes, Seconds, Milliseconds);
}