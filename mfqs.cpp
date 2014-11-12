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

    endTime = startTime + curQuantum;
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
        cout << "Start time: " << startTime << endl;

        q = 0;
        curQuan = quantum;
        int atime = currentP->getArrivalTime();
        cout << "Arrival time: " << atime << endl;

        if (currentP != NULL)
        {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

        if (currentP != NULL && atime <= startTime)
        {
            cout << "before run process first if" << endl;
            runProcess(currentP, q, curQuan, currentP->getBurstTime());
            cout << "after run process first if" << endl;
            procs++;
        }
        else
        {
            cout << "In else" << endl;
            cout << numQueues << endl;
            cout << q << endl;
            while (q < numQueues - 1 && &(queueList[q]) != NULL)
            {
                q++;
            }
            cout << "after while" << endl;

            if (q = 0 || q == numQueues - 1)
            {
                cout << "In q = 0 || q == numQueues" << endl;
                if (currentP != NULL)
                {
                    cout << "In next if" << endl;
                    while (currentP->getArrivalTime() > c.getTime())
                    {
                        cout << "Incrementing time" << endl;
                        c.incrementTime();
                        cout << "after Incrementing time" << endl;
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
                *currentP = queueList[q].front();
                queueList[q].pop();

                //run the process
                runProcess(currentP, q, curQuan, currentP->getBurstRemaining());
            }

        }

        cout << "BEFORE WHILE" << endl;
        while (&(queueList[numQueues - 1]) != NULL)
        {
            cout << "before next while" << endl;
            while (!queueList[numQueues - 1].empty())   //while the FCFS queue has more processes
            {
                cout << "in next while" << endl;
                *currentP = queueList[numQueues - 1].front();
                cout << ".front" << endl;
                queueList[numQueues - 1].pop(); //pop the first process
                cout << "before if" << endl;
                if (currentP->getLastTime() > atime)
                {
                    cout << "in if" << endl;
                    queueList[numQueues - 2].push(*currentP); //move up one queue if starving
                }
                else
                {
                    cout << "in else" << endl;
                    queueList[numQueues - 1].push(*currentP); //push to the back of FCFS if !starving
                }
            }
        }
        cout << "after while" << endl;

        currentP = processArray + procs;
    }
}


