#include "whsSch.h"
#include <cstdlib>


int main(int argc, char **argv){
	int timeQuantum = 0;
	int agefactor = 0;
		if(argc == 2){
		//timeQuantum = 2;agefactor = 5;
tryagain:
		cout << "Please choose a Time Quantum" << endl;
		cin >> timeQuantum;
		if ( timeQuantum <= 0 )
			goto tryagain;
//		cout << "Please choose a age factor" << endl;
//		cin >> agefactor;
		}
		else {
			
		}
		cout << "1" << endl;
		whsSch sched(timeQuantum);
		cout << "2" << endl;
		sched.loadinput(argv[1]);
		cout << "3" << endl;
		sched.UPDATE();
		cout << "4" << endl;
		clock_t start = clock();
		//sched.run();
		double duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
		cout << "duration: " << duration << endl;
		cout << "5" << endl;
		//sched.stats();
		cout << "6" << endl;
		exit(0);
	return 0;
}