#include "whsSch.h"
#include <cstdlib>


int main(int argc, char **argv){
	int timeQuantum = 0;
	int agefactor = 0;
		if(argc == 2){
tryagain:
		cout << "Please choose a Time Quantum" << endl;
		cin >> timeQuantum;
		if ( timeQuantum <= 0 )
			goto tryagain;

		}
		else {
			
		}
		whsSch sched(timeQuantum);
		sched.loadinput(argv[1]);
		sched.UPDATE();
		sched.run();
		sched.stats();
		exit(0);
	return 0;
}