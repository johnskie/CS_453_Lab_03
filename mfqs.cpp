#include "mfqs.h"

using namespace std;

MFQS::MFQS(int numQueues, int at, int quantum, Process *processArray)
{
    this->numQueues =  numQueues;
    this->at = at;
    this->quantum = quantum;
    this->processArray = processArray;
    totalWait = 0;
    totalTurnaround = 0;
    queueList[numQueues - 1];
    c = Clock();
    currentP = processArray;
    // initialization issue with queuelist? where is it initialized?
    for (int i = 0; i < numQueues - 1; i++)
    {
    	&queueList[i] =  NULL;
    }


}

void MFQS::runProcess(Process *currentProcess, int q1, int curQuantum, int currentRemaining)
{
    if (q1 == 0)
    {
        totalWait = c.getTime() - currentProcess->getArrivalTime();
    }
    else
    {
        totalWait = totalWait + c.getTime() + currentProcess->getLastTime();
    }

    endTime = startTime + curQuantum; // the endtime of a process is set to it's start time plus the current time quantum(i.e how long it ran)
    while (c.getTime() <= endTime && currentRemaining > 0)
    {
        c.incrementTime();
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

void MFQS::scheduleProcesses()
{
    int procs, q, curQuan;
    bool comp = false;

    while (currentP != NULL && !comp)
    {
        startTime = c.getTime();

        q = 0;
        curQuan = quantum;
        int atime = currentP->getArrivalTime();

        if (currentP != NULL && atime <= startTime)
        {
            runProcess(currentP, q, curQuan, currentP->getBurstTime());
            procs++;
        }
        else
        {
            cout << numQueues << endl;
            cout << q << endl;
            while (q < numQueues - 1 && &(queueList[q]) != NULL)
            {
                q++;
            }

            if (q == 0 || q == numQueues - 1)
            {
                if (currentP != NULL)
                {
                    while (currentP->getArrivalTime() > c.getTime())
                    {
                        c.incrementTime();
                    }
                }
                else
                {
                    comp = true;
                }
            }
            else if (q == numQueues - 2)
            {
                *currentP = queueList[q].front();
                queueList[q].pop();

                runProcess(currentP, q, currentP->getBurstTime(), currentP->getBurstTime());
            }
            else
            {
                for (int i = 0; i < q; i++)
                {
                    curQuan = curQuan * 2;
                }

                //set next process
                cout << "before currentP" << endl;
                *currentP = queueList[q].front();
                cout << "before pop" << endl;
                queueList[q].pop();
				cout << "before run process" << endl;
                //run the process
                runProcess(currentP, q, curQuan, currentP->getBurstRemaining());
            }

        }
        // mfqs gets this far with valgrind before starting an error cycle in the while loops
        // gets as far as before if and in if, keeps returning use of uninitialzed value of size 8
        // terminates after with default action of signal 11 (SIGSEGV)
        while (&(queueList[numQueues - 1]) != NULL)
        {
            while (!queueList[numQueues - 1].empty())   //while the FCFS queue has more processes
            {
                *currentP = queueList[numQueues - 1].front();
                queueList[numQueues - 1].pop(); //pop the first process
                if (currentP->getLastTime() > atime)
                {
                    queueList[numQueues - 2].push(*currentP); //move up one queue if starving
                }
                else
                {
                    queueList[numQueues - 1].push(*currentP); //push to the back of FCFS if !starving
                }
            }
        }
        cout << "before currentP2" << endl;

        currentP = processArray + procs;
    }
}


