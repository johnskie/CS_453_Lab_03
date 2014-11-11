#ifndef MFQS_H
#define MFQS_H

#include <iostream>
#include <string>
#include "Process.h"
#include "Clock.h"
#include <queue>

class MFQS
{
public:

    int numQueues, at, quantum, totalWait, totalTurnaround, startTime, endTime, numProcesses;
    Process* processArray, currentP;
    std::queue<Process> *queueList;
    std::queue<Process> curQueue;
    MFQS(int queues, int aTime, int quant, Process *pArray);
    void scheduleProcesses();
    void completeProcess(Process *currentProcess, int q, int quant, int currentRemaining);
    void initializeQL(std::queue<Process>* ql);
    Clock c;

};

#endif