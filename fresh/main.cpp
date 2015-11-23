#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Process.h"
#include "readin.h"

using namespace std;
void upgrade(){
//age up happens before downdgrade
}

void downgrade(){
//finish time quantum, go down queue
}

void schedule(){

}

int main(){
	vector<Process> readInFile(char*);

	vector<Process> processes = readInFile("in");
	/*vector<Process> lowband;
	vector<Process> highband;
	for(int i = 0; i < processes.size();i++){
	
		if(processes.at(i).getPriority() > 49){
			highband.push_back(processes.at(i));
		}else{
			lowband.push_back(processes.at(i));
		}
		
	}
	for(int i = 0; i < lowband.size();i++){
		cout << i << endl;
	}
	for(int i = 0; i < highband.size();i++){
		cout << i << endl;
	}*/
	
	
	
	
	return 0;
}