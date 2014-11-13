#include "RTS.h"

using namespace std;

RTS::RTS(int numQueues, int at, int quantum, int dline,  Process *processArray)
{
	this->at = at;
	this->quantum = quantum;
	this->processArray = processArray;
	this->dline = dline;
	
	totalwait = 0;
	totalTurnaround = 0;
	c = Clock();
	currentP = processArray;
}
// as far as i can remember rts cares aboutthe arrival time, the burst time(time quantum), and the end time
// once a process starts (sort by arrival time, then by priority and if that still doesnt do it, by PID)
// if the process finishes before it's alloted time quantum, insert the next process until the end of burst, then check for the next process to go (decrement runtime of inserted process as needed)
// make sure processes run by deadlines, if they cannot report them as failed (PID) and remove from queue
// ignore IO same as mfqs
void RTS::runProcess()
