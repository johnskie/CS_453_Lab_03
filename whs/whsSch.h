#ifndef whsSch_H
#define whsSch_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include "whsProcess.h"
#include <ctime>

using namespace std;
class whsSch {
	protected:
		vector<whsProcess> future_list;
		vector<whsProcess> done_list;
		vector<int> cpu_hist;
		int timeQ;
		int queue_total;
		int current_queue;
		int agepromotion;
		int ageouttime;
		vector<whsProcess> lowband;
		vector<whsProcess> highband;
		vector<whsProcess> waitQueue;
		vector<whsProcess> temp;
		bool interrupt;
		int thetime;
	public:
	
		whsSch(int timeQuantum ){
			cpu_hist.resize(100000);
			thetime = 540;
			timeQ = timeQuantum;
			interrupt = false;
			current_queue = 0;
			this->agepromotion = 10;
			this->ageouttime = 100;
		};
		
		class proxyCompareArrival {
			whsSch& that;
			public:
			proxyCompareArrival(whsSch &h) : that(h) {}
			bool operator()(whsProcess const &p1,whsProcess const &p2) const {
				return (p1.arrival  <= p2.arrival );
			}
		};
		struct sortclass{
			bool operator() (whsProcess i, whsProcess j){return(i.arrival < j.arrival || (i.arrival == j.arrival && i.priority < j.priority) || 
			(i.arrival == j.arrival && i.priority == j.priority && i.getPid() < j.getPid()));}
		} whsSortCriteria;
		
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
				int pid=0,burst=0,arrv=0,priorty=0,IO=0;
				char *pch;
				char *str = new char[strlen(input[i].c_str())+1];
				strcpy (str,input[i].c_str());
				
				pch = strtok (str," ");
				int count = 1;
				while(pch!=NULL && count < 7){
					if ( atoi(pch) != 0 ) { // make sure it is a number
						if (count == 1)
							pid=atoi(pch);
						if (count == 2)
							burst=atoi(pch);
						if (count == 3)
							arrv=atoi(pch);
						if (count == 4)
							priorty=atoi(pch);
						if (count == 6)
							IO=atoi(pch);
					}
					count++;
					pch = strtok(NULL," ");
				}
				delete[] str;
				if (pid != 0)
					future_list.push_back(whsProcess(pid,burst,arrv,priorty,agepromotion,IO));
			}
				//sort( future_list.begin(), future_list.end() , proxyCompareArrival(*this) );
			//print_all(0);
			
			std::sort(future_list.begin(),future_list.end(),whsSortCriteria);
			
			for(int i = 0; i < future_list.size(); i++){
				if(future_list.at(i).priority > 49 && future_list.at(i).burst >0){
					highband.push_back(future_list[i]);
				}else if(future_list.at(i).burst >0){
					lowband.push_back(future_list[i]);
				}
			}
			return 0;
		};
		void UPDATE(){
			int highestSize;
			if(highband.size() > lowband.size()){
				highestSize = highband.size();
			}else{
				highestSize = lowband.size();
			}
			for(int i = 0; i < highestSize;i++){
			//if the process has arrived age it and do the IO priority boost
				if(highband[i].arrival >= thetime && highband.size() < i){
					if(highband[i].IO > 0){
						highband[i].priority += highband[i].IO;
						if(highband[i].priority > 100){
							highband[i].priority = 99;
						}
					}
					highband[i].AGE();
					//if it has reached the ageout, boost priority
					if(highband[i].age >= ageouttime){
						highband[i].priority += 10;
						highband[i].age = 0;
						if(highband[i].priority > 100){
							highband[i].priority = 99;
						}
					}
				}
				if(lowband[i].arrival >= thetime && lowband.size() < i){
					if(lowband[i].IO > 0){
						lowband[i].priority += lowband[i].IO;
						if(lowband[i].priority > 50){
							lowband[i].priority = 49;
						}
					}
					lowband[i].AGE();
					//if it has reached the ageout, boost priority
					if(lowband[i].age >= ageouttime){
						lowband[i].priority += 10;
						lowband[i].age = 0;
						if(lowband[i].priority > 50){
							lowband[i].priority = 49;
						}
					}
				}
			}
			//for(int i = 0; i < lowband.size();i++){
			//if the process has arrived age it and do the IO priority boost
				
			//}
		}
		void UPDATE(int highestSize){
			for(int i = 0; i < highestSize;i++){
			//if the process has arrived age it and do the IO priority boost
				if(highband[i].arrival >= thetime && highband.size() < i){
					if(highband[i].IO > 0){
						highband[i].priority += highband[i].IO;
						if(highband[i].priority > 100){
							highband[i].priority = 99;
						}
					}
					highband[i].AGE();
					//if it has reached the ageout, boost priority
					if(highband[i].age >= ageouttime){
						highband[i].priority += 10;
						highband[i].age = 0;
						if(highband[i].priority > 100){
							highband[i].priority = 99;
						}
					}
				}
				if(lowband[i].arrival >= thetime && lowband.size() < i){
					if(lowband[i].IO > 0){
						lowband[i].priority += lowband[i].IO;
						if(lowband[i].priority > 50){
							lowband[i].priority = 49;
						}
					}
					lowband[i].AGE();
					//if it has reached the ageout, boost priority
					if(lowband[i].age >= ageouttime){
						lowband[i].priority += 10;
						lowband[i].age = 0;
						if(lowband[i].priority > 50){
							lowband[i].priority = 49;
						}
					}
				}
			}
			//for(int i = 0; i < lowband.size();i++){
			//if the process has arrived age it and do the IO priority boost
				
			//}
		}
		
		void run(){
			bool done = false;
			int toRemoveHigh;
			int toRemoveLow;
			int highestSize;
			int toRemove;
			if(highband.size() > lowband.size()){
				highestSize = highband.size();
			}else{
				highestSize = lowband.size();
			}
			while(!done){
				toRemoveHigh = -5;
				toRemoveLow = -5;
				toRemove = -5;
				
				
				//if we're out of highband, just try the low band
				if(!highband.empty()){
				if(done_list.size() >= 4836){
					sleep(1);
					cout << "inside highband" << endl;
				}
				//see if the high band has any arrivals that need to be run
					for(int i = 0; i < highestSize; i++) {
						if(highband[i].arrival <= thetime && i < highband.size()){
						//cout << "highband: " << i << endl;
							if(toRemoveHigh < 0){//if the temp is empty just push it on	
								toRemoveHigh=i;
							}else if(highband[toRemoveHigh].priority < highband[i].priority){//else compare to see who has a higher priority
								toRemoveHigh=i;
							}
							/*if(temp.empty()){//if the temp is empty just push it on
								temp.push_back(highband[i]);
								toRemove=i;
							}else if(temp[0].priority < highband[i].priority){//else compare to see who has a higher priority
								temp.pop_back();
								temp.push_back(highband[i]);
								toRemove=i;
							}*/
						}
			
						/*if(lowband[i].arrival <= thetime && i < lowband.size() && (toRemoveHigh < 0)){
						//cout << "lowband: " << i << endl;
							if(toRemoveLow < 0){//if the temp is empty just push it on the temp variable
								toRemoveLow=i;
							}else if(lowband[toRemoveLow].priority < lowband[i].priority){//else compare to see who has a higher priority
								toRemoveLow=i;
							}
						}*/

						
					}
					//take the value out of highband that was taken
					/*if(!temp.empty()){
						highband.erase(highband.begin() + toRemove);
					}*/
					if(!(toRemoveHigh < 0)){
						temp.push_back(highband[toRemoveHigh]);
						highband.erase(highband.begin() + toRemoveHigh);
					}/*else if(!(toRemoveLow < 0)){
						temp.push_back(lowband[toRemoveLow]);
						lowband.erase(lowband.begin() + toRemoveLow);
					}*/
				}
				//try a low burst if the high didn't have any to load and the lowband isn't empty
				if(temp.empty() && !lowband.empty()){
				/*if(done_list.size() >= 4836){
					sleep(1);
					cout << "inside low" << endl;
				}*/
					for(int i = 0; i < highestSize; i++) {
						if(lowband[i].arrival <= thetime && i < lowband.size()){/////////////////////////////////////////////////////
						//cout << "lowband: " << i << endl;
							/*if(toRemoveLow < 0){//if the temp is empty just push it on the temp variable
								toRemoveLow=i;
							}else if(lowband[toRemoveLow].priority < lowband[i].priority){//else compare to see who has a higher priority
								toRemoveLow=i;
							}*/
							if(temp.empty()){//if the temp is empty just push it on the temp variable
								temp.push_back(lowband[i]);
								toRemove=i;
							}else if(temp[0].priority < lowband[i].priority){//else compare to see who has a higher priority
								temp.pop_back();
								temp.push_back(lowband[i]);
								toRemove=i;
							}
						}/////////////////////////////////////////////////////////////////
					}
					//take the value out of the lowband that was taken
					/*if(!(toRemoveLow < 0)){
						temp.push_back(lowband[toRemoveLow]);
						lowband.erase(lowband.begin() + toRemoveLow);
					}*/
					
					if(!temp.empty()){
						lowband.erase(lowband.begin() + toRemove);
					}
					//if both bands are empty we'll finsih up here
				}
				
				if(highband.size() > lowband.size()){
				highestSize = highband.size();
				}else{
				highestSize = lowband.size();
				}
				
				if(!temp.empty()){
					int processTicks = 0;
					//cout << "timeq: " << timeQ << endl;
					//cout<< "empty temp var: " << temp.empty() << endl;
					
						while(processTicks < timeQ && 0 < temp[0].timeRemaining){
							if(processTicks == timeQ-2 && temp[0].IO > 0){
								//on the second to last tickk, to IO. i should review this
								temp[0].IO =0;
							}
							UPDATE(highestSize);
							thetime++;
							temp[0].timeRemaining--;
							processTicks++;
						}
						//if the timeremaining on the process is zero. put it in the finished list
						if(temp[0].timeRemaining == 0){
							temp[0].finishTime = thetime;
							done_list.push_back(temp[0]);
							//cout << "finished list size: " << done_list.size() << endl;
							temp.erase(temp.begin());
						//else reduce it by the time it spent on the clock and put back into proper band
						}else if(temp[0].originalpriority < 50){
							temp[0].priority -= processTicks;
							if(temp[0].priority < temp[0].originalpriority){
								temp[0].priority = temp[0].originalpriority;
							}
							lowband.push_back(temp[0]);
							temp.erase(temp.begin());
						}else{
							temp[0].priority -= processTicks;
							if(temp[0].priority < temp[0].originalpriority){
								temp[0].priority = temp[0].originalpriority;
							}
							highband.push_back(temp[0]);
							temp.erase(temp.begin());
						}
					
				//if we don't have any available but the low or highband aren't empty. just move a clock tick forward
				}else if(!highband.empty() || !lowband.empty() && temp.empty()){
					UPDATE(highestSize);
					thetime++;
					cout << "aint processing shit" << endl;
				}else{
				cout << "were done muthafucka" << endl;
					done=true;
				}
				
				
				//will have to load the temp back in to the proper spot if it still has a timeRemaining
				
				//gotta load in the proper one to perform for the timequantum or until done
				
			}
		}
};
#endif