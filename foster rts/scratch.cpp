priority_queue<rtsProcess, vector<rtsProcess>, CompareProcesses> pq; // initialize the priority queue
// this contains classes of rtsProcess

class CompareProcesses {
			public:
				bool operator()(rtsProcess i, rtsProcess j)// returns true if i is earlier than j
				{
					if (i.arrival < j.arrival) return true;
					if (i.deadline < j.deadline && i.arrival < j.arrival) return true;
					if (i.deadline < j.deadline && i.arrival < j.arrival && i.pid < j.pid) return true;
					return false;
				}
			};


/*
it was reccomended to have two data structures, one sorted by arrival time
and one sorted by deadline. every clock tick, check if a new process is arriving, then 
shift it from the one structure to the deadline structure and sort based on that?


sudo get apt install g++


wrap if debug around the print statements
*/


#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct Time {
    int h; // >= 0
    int m; // 0-59
    int s; // 0-59
};

class CompareTime {
public:
    bool operator()(Time& t1, Time& t2)
    {
       if (t1.h < t2.h) return true;
       if (t1.h == t2.h && t1.m < t2.m) return true;
       if (t1.h == t2.h && t1.m == t2.m && t1.s < t2.s) return true;
       return false;
    }
};

int main()
{
    priority_queue<Time, vector<Time>, CompareTime> pq;

    // Array of 4 time objects:

    Time t[4] = { {3, 2, 40}, {3, 2, 26}, {5, 16, 13}, {5, 14, 20}};
 
    for (int i = 0; i < 4; ++i)
       pq.push(t[i]);

    while (! pq.empty()) {
       Time t2 = pq.top();
       cout << setw(3) << t2.h << " " << setw(3) << t2.m << " " <<
       setw(3) << t2.s << endl;
       pq.pop();
    }

    return 0;
}

//The program prints the times from latest to earliest:
    
    5  16  13
    5  14  20
    3   2  40
    3   2  26

//If we wanted earliest times to have the highest priority, we would redefine CompareTime like this:

class CompareTime {
public:
    bool operator()(Time& t1, Time& t2) // t2 has highest prio than t1 if t2 is earlier than t1
    {
       if (t2.h < t1.h) return true;
       if (t2.h == t1.h && t2.m < t1.m) return true;
       if (t2.h == t1.h && t2.m == t1.m && t2.s < t1.s) return true;
       return false;
    }
};

#ifndef RTS_H
#define RTS_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <queue>
#include "rtsProcess.h"

using namespace std;


class rts {
  protected:
    vector<rtsProcess> proc_list;
    int clock;
    vector<int> cpu_hist;
    bool isHard;
  public:
    rts() { clock =0; };
    rts(bool hardness) { clock =0; isHard = hardness; };
    ~rts() { };
    //priority_queue<rtsProcess, vector<rtsProcess>, CompareProcesses> pq; // initialize the priority queue (elsewhere?)
    
    class proxyCompare {
      rts& that;
      public:

      proxyCompare(rts &h) : that(h) {}
      bool operator()(rtsProcess const &p1,rtsProcess const &p2) const {
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
          return (p1.deadline > p2.deadline);
      }
      /* create a process (class) whose purpose is to compare values among processes of the priority queue
      // return true if they match an order (arrival, then deadline, then pid)*/
      class CompareProcesses {
      public:
        bool operator()(rtsProcess i, rtsProcess j)
        {
          

          return (i.deadline > j.deadline);
          
        
        }
      }; 
    };
  };



    /*
    struct sortclass{
      bool operator() (rtsProcess i, rtsProcess j){return(i.arrival < j.arrival || (i.arrival == j.arrival && i.deadline < j.deadline) || 
      (i.arrival == j.arrival && i.deadline == j.deadline /*&& i.pid() < j.pid()));}
    } rtsSortCriteria;*/

    int loadinput(char *filename) {
      ifstream testfile(filename); 
      //make sure file exists before calling sed
      if (!testfile) {
        cerr << "error loading input file!\n";
        exit(1);
        return 0;
      }
      testfile.close();
      string cmd = "sed \'s/\t/ /g\' " + string(filename) + " > sample.clean";
      system(cmd.c_str());
      ifstream infile("sample.clean");
      if (!infile){
        cerr << "error loading file after clean-up!\n";
        return 0;
      }

      vector<string> input;
      string tmp_str;
      while( !infile.eof() )
      {
        getline(infile, tmp_str);
        input.push_back(tmp_str);
      }
      infile.close();
      system("rm sample.clean");

      //all lines loaded into string vector :input:
      //now parse through string vector and make rtsProcess vector
      for(unsigned int i=0; i < input.size() ; i++) {
        int pid=0,burst=0,arrv=0,deadline=0;
        char *pch;
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
          proc_list.push_back(rtsProcess(pid,burst,arrv,deadline));//proc_list not sorted by arrival time? change proc_list to another pq sorted by deadline
          //pq.push(rtsProcess(pid,burst,arrv,deadline)); // move so we only add to pq when arrival time, move from proc_list to pq based on arrival
      }
      print_all(0);
      
      return 0;
    };

    int run_sched(){
      bool doneWithLast = false;
      int failedProcesses;
      rtsProcess current = pq.top();
      vector<rtsProcess>::iterator first = proc_list.begin(); //at this point what we need to do is shift the processes from proc_list to pq on arrival time
      while(!doneWithLast) {
        if(first==proc_list.end()) //unknown if we still need this line
          goto skip;
        //sort( first, proc_list.end() , proxyCompare(*this) ); // if we change proc_list to a pq, then it's already sorted by the criteria, so no need for sort
        //sort( proc_list.begin(),proc_list.end(),rtsSortCriteria); 
        if( current->arrival <= clock) {
          if(clock > first->deadline){
            if (this->isHard){
              cout << "Process " << first->pid <<" failed to reach deadline, hardtime environment aborting!" << endl; 
              exit(1);
            }
            else {
              if (first->pid != 0)
              cout << "Process " << first->pid << " failed to reach deadline in soft RT environment, process aborting" << endl;
              first->failed = true;
              failedProcesses++;
              cout << "the number of processes that failed is: " << failedProcesses << endl;
              goto skip;
            }
          }
          if(first->burst == first->timeRemaining) {
          // just finished waiting.. non preemptive.
            first->doneWaiting = clock; 
          }
          cpu_hist.push_back(first->pid);
          first->timeRemaining--;
          if(first->timeRemaining <= 0){
            skip:
            first->finishTime = clock;
            if(first == proc_list.end()){
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
     void stats() {
      double avgTurn = 0;
      double avgWait = 0;
      double count = 0;
      vector<rtsProcess>::iterator it;
      for(it = proc_list.begin(); it != proc_list.end(); it++){
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

/*
trace steps:
traced to printall at end of loadinput (at this time proc_list contains all values in correct pid order)


verify at each step
locate inherent point of failure
*/
    
#endif