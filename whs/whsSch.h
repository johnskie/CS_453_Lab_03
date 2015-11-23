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
		bool interrupt;
		int thetime;
	public:
	
		whsSch(int timeQuantum ){
			cpu_hist.resize(100000);
			thetime = 0;
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
					future_list.push_back(whsProcess(pid,burst,arrv,priorty,agepromotion));
			}
				//sort( future_list.begin(), future_list.end() , proxyCompareArrival(*this) );
			//print_all(0);
			
			std::sort(future_list.begin(),future_list.end(),whsSortCriteria);
			
			for(int i = 0; i < future_list.size(); i++){
				cout << "pid: " << future_list.at(i).getPid() << endl;
				cout << "priority: " << future_list.at(i).priority << endl;
				/*if(future_list.at(i).priority > 49){
					highband.push_back(future_list[i]);
				}else{
					lowband.push_back(future_list[i]);
				}*/
			}
			cout << "==============band stuff start============"<< endl;
			for(int i = 0; i < highband.size(); i++){
				cout << highband.at(i).getPid() << endl;
			}			cout << "=========================="<< endl;

			for(int i = 0; i < lowband.size(); i++){
				cout << lowband.at(i).getPid() << endl;
			}
						cout << "============band stuff end=============="<< endl;

			return 0;
		};
		
		void UPDATE(){
		
		}
		
		void run(){
			bool done = false;
			//while(!done){
				
			//}
			
		}
		
		void dosomeschedulestuff(){
		
		}
		
		void updateClock(){
			thetime++;
			UPDATE();
		}
};
#endif