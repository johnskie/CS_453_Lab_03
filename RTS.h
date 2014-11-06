#ifndef RTS_H
#define RTS_H

#include <iostream>
#include <string>
#include "Scheduler.h

# initial sort at beginning is the most important

using namespace std;

class RST : public Scheduler{
public:
	RTS() : Scheduler() {};
	RTS(int queues, int aTime, int quant, int deadline);
	~RTS() {};


	void run();
	virtual void scheduleProcesses();
	//
	void runProcess(Process * currentProcess, int q, int quant, int currentRemaining);



private
//class variables
	int numQueues;
	int ageTime;
	int timeQuant;
	int totalWait;
	int totalTurnaround;

	int arrivalTime;
	int startTime;
	int endTime;
	int processCount;
	
	queue<Process> * queuelist;
	queue<Process> holdingQueue;
