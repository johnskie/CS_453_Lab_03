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
		cout << "1" << endl;
		sch sched(time,numberOfQueues,agefactor);
		cout << "2" << endl;
		sched.loadinput(argv[1]);
		cout << "3" << endl;
		sched.UPDATE();
		cout << "4" << endl;
		clock_t start = clock();
		sched.run();
		double duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
		cout << "duration: " << duration << endl;
		cout << "5" << endl;
		sched.stats();
		cout << "6" << endl;
		exit(0);
	return 0;
}