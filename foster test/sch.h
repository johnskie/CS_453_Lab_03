#ifndef sch_H
#define sch_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include "mfqsProcess.h"
#include <ctime>


using namespace std;
class sch {
	protected:
		vector<mfqsProcess> future_list;
		vector<mfqsProcess> done_list;
		vector<int> cpu_hist;
		int timeQ;
		int queue_total;
		int current_queue;
		int agefactor;
		vector<mfqsProcess> queues[5]; 	
		bool interrupt;
		int thetime;
		double updateDuration;
		double runDuration;
		double rrDuration;
		double fcfsDuration;
		double updateClockDuration;
		
	public:

		sch(int time, int number,int agefactor) 
		{ 
			cpu_hist.resize(100000);
			queue_total = number;
			for (int i=0;i<queue_total;i++){
				queues[i].resize(100);
			}cout << "after the loop" << endl;
			thetime = 0;
			timeQ = time;
			interrupt = false;
			current_queue = 0;
			this->agefactor = agefactor;
		};
		~sch() { };

		class proxyCompareArrival {
			sch& that;
			public:
			proxyCompareArrival(sch &h) : that(h) {}
			bool operator()(mfqsProcess const &p1,mfqsProcess const &p2) const {
				return (p1.arrival  <= p2.arrival );
			}
		};
		int loadinput(char *filename) {
			ifstream testfile(filename); 
			//make sure file exists before calling sed
			if (!testfile) {
				cerr << "error loading input file!\n";
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
			//now parse through string vector and make mfqsProcess vector
			for(unsigned int i=0; i < input.size() ; i++) {
				int pid=0,burst=0,arrv=0,priorty=0;
				char *pch;
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
						if (count == 4)
							priorty=atoi(pch);
					}
					count++;
					pch = strtok(NULL," ");
				}
				delete[] str;
				if (pid != 0)
					future_list.push_back(mfqsProcess(pid,burst,arrv,priorty,agefactor));
			}
				//sort( future_list.begin(), future_list.end() , proxyCompareArrival(*this) );
			//print_all(0);
			
			return 0;
		};
		
		void UPDATE(){
			// aging
			std::clock_t start;
			start = std::clock();
			
			mfqsProcess* it = &queues[this->queue_total-1][0];
			for(unsigned int i=0; i<queues[this->queue_total-1].size(); i++){
				it = &queues[this->queue_total-1][i];
				it->AGE();
				if(it->aged())
				{
					it->age = 0;
					queues[this->queue_total - 2].push_back( mfqsProcess(*it) );
					queues[this->queue_total - 1].erase( queues[this->queue_total-1].begin() + i );
					if( current_queue == queue_total)
						interrupt = true;
				}
			}
			// future cheching
			for(unsigned int i=0; i < future_list.size() ; i++){
				it= &future_list[i];
				if(thetime >= it->arrival)
				{
					queues[0].push_back(*it);
					future_list.erase( future_list.begin()+i );
					if( current_queue != 0)
						interrupt = true;
				}	
			}	
			updateDuration += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		}
		
		void run(){
			std::clock_t start;
			start = std::clock();
			bool done = false;
			while(!done){
				interrupt = false;
				for( int i=0; i < queue_total && !interrupt ; i++ ) {
					current_queue = i;
					if (!queues[i].empty() && i != queue_total-1)
						do_rr_q(i); // do rr on q(i) 
					else {
						if(!queues[i].empty() && i == queue_total-1)
							do_fcfs(i);
						else //everything empty
							if (!future_list.empty()){
								update_clock();
								cpu_hist.push_back(-1);
							}
							else{
								bool allEmpty=true;
								for(int j=0; j<queue_total && allEmpty; j++){
									if (!queues[j].empty())
										allEmpty=false;
								}
								if (allEmpty)
									done=true;
							}
					}
				}
			}
			runDuration += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			print_all(0);
		};
		
		
		int do_rr_q(int i){
			//cout << "do_rr_q(" << i << ")..." << endl;
			std::clock_t start;
			start = std::clock();
			int subtime = 0;
			while(!interrupt && !queues[i].empty()){
				mfqsProcess* first = &queues[i][0];
				if (first->burst == first->timeRemaining)
					first->doneWaiting = thetime;
				for(subtime = 0; (subtime < timeQ*(i+1)) && !interrupt && first->timeRemaining > 0; subtime++){
					//cout << "pid " << first->getPid() << " remaining " << first->timeRemaining << endl; 	
					first->timeRemaining--;
					cpu_hist.push_back(first->getPid());
					update_clock(); //calls update;
					first = &queues[i][0];
				}			
				if( first->timeRemaining <= 0){
					first->finishTime = thetime;
					done_list.push_back( *first );
				} else{
					//cout << "moving pid " << first->getPid() << " to [" << i << "]" << endl;
					queues[i+1].push_back( mfqsProcess(*first) ); //push
				}
				queues[i].erase( queues[i].begin() );
			}
			
			rrDuration += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			return (int)interrupt;
		};
		int do_fcfs(int i) {
			std::clock_t start;
			start = std::clock();
			while(!interrupt && !queues[i].empty()){
				mfqsProcess* first = &queues[i][0];
				for(; !interrupt && first->timeRemaining > 0 ;){
					first->timeRemaining--;
					cpu_hist.push_back(first->getPid());
					update_clock();
					first = &queues[i][0];
				}
				if (first->timeRemaining <= 0 ){
					first->finishTime = thetime;
					done_list.push_back( *first );
					queues[i].erase( queues[i].begin() );
				}
			}
			fcfsDuration += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			return (int)interrupt;
		};
		void update_clock(){
			std::clock_t start;
			start = std::clock();

			thetime++;
			UPDATE();
			
			updateClockDuration += ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		};
		void print_all(int k){
			vector<mfqsProcess>::iterator fut;
			vector<mfqsProcess>::iterator active;
			cout << "Future Processes" << endl;
			for(fut = future_list.begin(); fut != future_list.end(); fut++){
				cout << *fut << endl;
			}
			for(int i=0; i < queue_total; i++){
				cout << "Active Process Queue[" <<i<<"]" << endl;
				for(active = queues[i].begin(); active != queues[i].end(); active++){
					cout << *active << endl;
				}
			}
			cout << "CPU history" <<endl;
			for(unsigned int i=0; i<cpu_hist.size(); i++){
				cout << cpu_hist[i] << " ";
			} cout << endl;
			cout << "times" << endl;
		cout << "updateDuration: " << updateDuration << endl;
		cout << "runDuration: " << runDuration << endl;
		cout << "rrDuration: " << rrDuration << endl;
		cout << "fcfsDuration: " << fcfsDuration << endl;
		cout << "updateClockDuration: " << updateClockDuration << endl;
		};
	
		void stats() {
			double avgTurn = 0;
			double avgWait = 0;
			double count = 0;
			vector<mfqsProcess>::iterator it;
			for(it = done_list.begin(); it != done_list.end(); it++){
				count++;
				avgTurn += (it->finishTime+1 - it->arrival);
				avgWait += (it->doneWaiting - it->arrival);
			}
			avgTurn /= count;
			avgWait /= count;
			cout << "Average Turnaround Time: " << avgTurn << endl;
			cout << "Average Waiting Time: " << avgWait << endl;
		
		};
};




#endif