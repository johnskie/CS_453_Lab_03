#include "sch.h"
#include <cstdlib>


int main(int argc, char **argv){
	int time = 0;
	int agefactor = 0;
	int numberOfQueues = 0;
		if(argc == 2){
		//time = 2;agefactor = 5;
tryagain:
		cout << "Please choose a Time Quantum" << endl;
		cin >> time;
		if ( time <= 0 )
			goto tryagain;
doover:
		cout << "Please choose a number of queues(3-5)" << endl;
		cin >> numberOfQueues;
		if (numberOfQueues > 5 || numberOfQueues < 3)
			goto doover;
		cout << "Please choose a age factor" << endl;
		cin >> agefactor;
		}
		else {
			cout << "input file error. please input as ./program [input in parenthesis]" << endl;
			return  0;
		}
		sch sched(time,numberOfQueues,agefactor);
		sched.loadinput(argv[1]);
		sched.UPDATE();
		sched.run();
		sched.stats();
		exit(0);
	return 0;
}