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
	public:
	
		whsSch(){
		
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
		
		}
		
		void run(){
			
		}
		
		void dosomeschedulestuff(){
		
		}
		
		void updateClock(){
			thetime++;
			UPDATE();
		}
};
#endif