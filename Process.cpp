#include "Process.h"

Process::Process(int pid, int burst, int arrival, int priority, int deadline, int io)
{
    this->pid = pid;
    burstTime = burst;
    arrivalTime = arrival;
    this->priority = priority;
    this->deadline = deadline;
    io_ticks = io;
}

int Process::getPID()
{
    return this->pid;
}

int Process::getBurstTime()
{
    return this->burstTime;
}

int Process::getArrivalTime()
{
    return this->arrivalTime;
}

int Process::getPriority()
{
    return this->priority;
}

int Process::getDeadline()
{
    return this->deadline;
}

int Process::getIO()
{
    return io_ticks;
}

int Process::getLastTime()
{
	return this->lastTime;
}

bool Process::isComplete()
{
    bool comp = false;

    if (this->burstRemaining < 1)
    {
        comp = true;
    }

    return true;
}

void Process::decrementTime()
{
    this->burstRemaining--;
}

void Process::setLastTime(int t){
	this->lastTime = t;
}


