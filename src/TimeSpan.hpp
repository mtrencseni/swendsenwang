#ifndef TIMESPAN_H
#define TIMESPAN_H

class TimeSpan
{
public:
	short Milliseconds;
	short Seconds;
	short Minutes;
	short Hours;
	long TotalMilliseconds;
	long TotalSeconds;
	long TotalMinutes;

	TimeSpan();
	TimeSpan(long start, long end);
	TimeSpan(long totalMilliseconds);

	TimeSpan operator+=(TimeSpan other);

	void Report(char* text);
};

#endif
