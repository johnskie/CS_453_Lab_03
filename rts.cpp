#include "RTS.h"

using namespace std;

RTS::RTS(int numQueues, int at, int quantum, Process *processArray)
{
	this->numQueues = numQueues;
	this->at = at;
	this->quantum = quantum;
	this->processArray = processArray;
	totalwait = 0;
	totalTurnaround = 0;
	queueList[numQueues - 1];
	c = Clock();
	currentP = processArray;
}

void RTS::runProcess(Process *currentProcess, int q1, int curQuantum, int currentRemaining)
{
	if (q1 == 0)
	{
		totalWait = c.getTime() - currentProcess->getArrivalTime();
	}
	else
	{
		totalWait = totalWait = c.getTime() + currentProcess->getLastTime();
	}

	endTime = startTime + curQuantum;
	while (c.getTime() <= endTime && currentRemaining > 0)
	{
		c.incrementTme();
		currentProcess->decrementTime();
	}

	if (currentRemaining > 0)
	{
		currentProcess->setLastTime(endTime);
		queueList[q1 + 1].push(*currentProcess);
	}
	else
	{
		int diff = c.getTime() - currentProcess->getArrivalTime();
		totalTurnaround = totalTurnaround + diff;
	}

}

void RTS::scheduleProcesses()
{
	int procs, q, curQuan;













