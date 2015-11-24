#include <iostream>
#include <string>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {

	cout << endl;
	cout << "Choose scheduling algorithm" << endl;
	cout << "(0) MFQS" << endl;
	cout << "(1) RTS " << endl;
	cout << "(2) WHS " <<endl;
	cout << "(3) ABORT" << endl;
	int choice = 4;
	char* filename = new char[256];
	cin >> choice;
		
	//int pid = 0, burst = 0,arr = 0, pri = 0, dead = 0, quantum = 0;		
	//char outFilename[35] = "temptempinput";
       //ofstream outFile(outFilename);
	int done = 1;
	if (choice == 3)
		exit(0);
	cout << endl << "Please enter filename for process information." << endl;
	cin >> filename;
	afterread:
	char* programName = new char[256];
	char* pathname = new char[256];
	switch (choice) {
		case 0:
			programName = "mfqs";
			pathname = "mfqs/mfqs";
			break;
		case 1:
			programName = "rts";
			pathname = "rts/rts";
			break;
		case 2:
			programName = "whs";
			pathname = "whs/whs";
			break;
		default:
			cout << "Please choose a proper option." << endl;
			break;	
	}
	char *cmd[] = { programName, filename, (char*)0}; 
	pid_t child_pid = fork();
	int status, ch_stat;
	if( child_pid < 0) 
		cout << "error forking!" << endl;
	if( child_pid == 0) //child
		execv(pathname,cmd);
	else { //parent
		while( (status=wait(&ch_stat)) != child_pid ) {
			if( status < 0 && errno == ECHILD) 
				break;
			errno = 0;
		}
	}

	
	return 0;
}