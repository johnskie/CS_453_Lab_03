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




vector<Process> readInFile(char* filename){
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
	
}

vector<Process> mfqsCleanAndSort(vector<Process> in){
	/*int j = 0;
	bool swapped = true;
	while(swapped){
		swapped = false;
		j++;
		for(int i = 1; i <= in.size(); i++){
			if(in.at(i-1).getArrivalTime() < in.at(i).getArrivalTime() && in.at(i-1).getPriority() != in.at(i).getPriority() || in.at(i-1).getArrivalTime() == in.at(i).getArrivalTime() && in.at(i-1).getPriority() > in.at(i).getPriority()){
				in[i-1].swap(in[i]);
			}
		}
	}*/
}

