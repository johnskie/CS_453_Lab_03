#ifndef RTS_H
#define RTS_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include "RTSprocess.h"

using namespace std;


class rts {
	protected:
		vector<rtsProcess> proc_list;
		int clock;
		vector<int> cpu_hist;
		bool isHard;
	public:
		rts() { clock = 0; };
		rts(bool hardness) { clock = 0; isHard = hardness; };
		~rts() { };
		
		class proxyCompare {
			rts& that;
			public:
			proxyCompare(rts &h) : that(h) {}
			bool operator()(rtsProcess const &p1, rtsProcess const &p2) const {
				bool oneIsInFuture = false;
				bool twoIsInFuture = false;
				if (p1.arrival > that.clock)
					oneIsInFuture = true;
				if (p2.arrival > that.clock)
					twoIsInFuture = true;
				if (oneIsInFuture && !twoIsInFuture)
					return false;
				if (!oneIsInFuture && twoIsInFuture)
					return true;
				else	
					return (p1.deadline < p2.deadline);
			}
		};

		int loadinput(char *filename) {
			ifstream testfile(filename);
			//make sure that the test file exists before calling sed
			if (!testfile) {
				cerr << "error loading input file!\n";
				exit(1);
				return 0;
			}
			testfile.close();
			string cmd = "sed \'s/\t/ /g\'" + string(filename) + " > sample.clean";
			system(cmd.c_str());
			ifstream infile("sample.clean");
			if (!infile) {
				cerr << "error loading file after clean-up!\n";
				return 0;
			}

			vector<string> input;
			string tmp_str;
			while( !infile.eof())
			{
				getline(infile, tmp_str);
				input.push_back(tmp_str);
			}
			infile.close();
			system("rm sample.clean");
// all lines have been loaded into string vector :input:
// now parse through the created string vector and make RTSprocess vector
			for(unsigned int i=0; i < input.size() ; i++) {
				int pid=0,burst=0,arrv=0,deadline=0;
				char *pch;
				//test code for
				/*char str[ strlen(input[i].c_str())+1 ];
				strcpy (str,input[i].c_str());*/
				char *str = new char[strlen(input[i].c_str())+1];
				strcpy (str,input[i].c_str());
				
				pch = strtok (str," ");
				int count = 1;
				while(pch!=NULL && count < 6){
					if ( atoi(pch) != 0 ) { // make sure it is a number
						if (count == 1)
							pid=atoi(pch);
						if (count == 2)
							burst=atoi(pch);
						if (count == 3)
							arrv=atoi(pch);
						if (count == 5)
							deadline=atoi(pch);
					}
					count++;
					pch = strtok(NULL," ");
				}
				delete[] str;
				if (pid != 0)
					proc_list.push_back(rtsProcess(pid,burst,arrv,deadline));
			}
			print_all(0);

			return 0;
		};

// method to actually run the scheduler
		int run_sched(){
			cout << "test1" << endl;
			//self explanatory, if we aren't done with the last process, this bool is false
			bool doneWithLast = false;
			vector<rtsProcess>::iterator first = proc_list.begin(); // returns first(pointer) to the beginning of proc_list
			cout << "test2" << endl;
			cout << doneWithLast << endl;
			while(!doneWithLast) {
				if(first==proc_list.end()) // if the pointer is equal to the end of proc_list then go to skip
					cout << "test3" << endl;
					goto skip;
					cout << "test126" << endl;
				sort( first, proc_list.end() , proxyCompare(*this) );
				cout << "test4" << endl;
				//time checking for hard and soft environments, deadlines determine if we meet the exit conditions
				if( first->arrival <= clock) {
					cout << "test5" << endl;
					cout << clock << endl;
					if(clock > first->deadline){
						if (this->isHard){
							cout << "Process " << first->pid <<" failed to reach deadline, hardtime environment aborting!" << endl;	
							exit(1);
						}
						else {
							if (first->pid != 0)
							cout << "Process " << first->pid << " failed to reach deadline in soft RT environment, process aborting" << endl;
							first->failed = true;
							goto skip;
						}
					}
					if(first->burst == first->timeRemaining) {
					// this means that the job has just finished waiting  this version is non preemptive.
						first->doneWaiting = clock;	
					}
					cpu_hist.push_back(first->pid);
					first->timeRemaining--;
					if(first->timeRemaining <= 0){
						skip: // here in skip get the member finishTime from first and set it = to clock (0) 
						cout << "test16" << endl;
						cout << clock << endl;
						first->finishTime = clock; //error in this line, error concerning null value?(segfault)
						cout << clock << endl;
						cout << "test17" << endl;
						if(first == proc_list.end()){
							cout << "test18" << endl;
							doneWithLast = true;
						}
						else{
							first++;
						}
					}
				} else {
					cpu_hist.push_back(0);
				}
				this->clock++;
				
			} 
			print_all(1);
			return 0;
		};
		
// method to find our average turnaround and wait times
		void stats() {
			double avgTurn = 0;
			double avgWait = 0;
			double count = 0;
			vector<rtsProcess>::iterator it;
			for (it = proc_list.begin(); it != proc_list.end(); it++){
				if(!it->failed){
					count++;
					avgTurn += (it->finishTime+1 - it->arrival);
					avgWait += (it->doneWaiting - it->arrival);
					
				}
			}
			avgTurn /= count;
			avgWait /= count;
			cout << "Average Turnaround Time: " << avgTurn << endl;
			cout << "Average Waiting Time: " << avgWait << endl;

		};

		void print_all(int endresult) {
			if (endresult !=1){
				cout << this->clock <<"\n\tpid\tburst\tarrival\tdeadline\ttime remaining\n";
				for(unsigned int i=0; i < proc_list.size() ; i++) {
					cout << proc_list.at(i) << endl;
				}
			}
			else {
				for(unsigned int i=0; i<cpu_hist.size(); i++) {
					cout << cpu_hist.at(i) << " ";
				}
			}
			cout << endl;
		};
		
};

#endif


/*
initial code, nonfunctional, scrapped for alternate methods above

	int at, quantum, totalWait, totalTurnaround, startTime, endTime, numProcesses;
	process *processArray, *currentP;
	std::queue<Process> *queueList;
	std::queue<Process> curQueue;
	RTS(int queues, int aTime, int quant, Process *pArray);
	void scheduleProcesses();
	void runProcess (Process *currentProcess, int q, int quant, int currentRemaining);
	void initializeQL(std::queue<Process>ql);
	Clock c;
	*/