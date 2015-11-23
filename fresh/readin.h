#ifndef READIN
#define READIN

#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include "Process.h"
#include <vector>

using namespace std;

class readin{
	
	public:
		vector<Process> readInFile(char* filename);
		vector<Process> mfqsCleanAndSort(vector<Process> in);
		
};
#endif