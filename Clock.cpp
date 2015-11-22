#include "Clock.h"

Clock::Clock()
{
    this->time = 0;
}

void Clock::incrementTime()
{
	this->time++;
}

int Clock::getTime()
{
	return this->time;
}

