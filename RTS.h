#ifndef RTS_H
#define RTS_H

#include <iostream>
#include <string>
#include "Clock.h"
#include "Process.h"
#include <queue>

class RTS
{
public:

	int at, quantum, totalWait, totalTurnaround, startTime, endTime, numProcesses;
	process *processArray, *currentP;
	std::queue<Process> *queueList;
	std::queue<Process> curQueue;
	RTS(int queues, int aTime, int quant, Process *pArray);
	void scheduleProcesses();
	void runProcess (Process *currentProcess, int q, int quant, int currentRemaining);
	void initializeQL(std::queue<Process>ql);
	Clock c;
};

#endif
