#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include "Process.h"
#include <vector>
#include "readin.h"

using namespace std;

/*vector<Process> readInFile(char* filename){
	std::ifstream file(filename);
    std::string str; 
	
	std::vector<Process> retval;
	int i = 0;
    while (std::getline(file, str))
    {
		std::vector<int> string_list;
		if(i != 0){
			istringstream ss(str);
			
			for(int word; ss >> word;){
				string_list.push_back(word);
			}
			Process temp;
			temp.setPID(string_list.at(0));
            temp.setArrivalTime(string_list.at(2));
            temp.setBurstTime(string_list.at(1));
            temp.setBurstRemaining(string_list.at(1));
            temp.setLastTime(string_list.at(2));
            temp.setIO(string_list.at(5));
            temp.setPriority(string_list.at(3));
            temp.setDeadline(string_list.at(4));
			retval.push_back(temp);
		}
	i++;
    }
	for(int i = 0; i < retval.size();i++){
		cout << retval.at(i).getPriority() << endl;
	}
	return retval;
	
}*/

/*void MFQS::runProcess(Process *currentProcess, int q1, int curQuantum, int currentRemaining)
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

}*/

