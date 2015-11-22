#ifndef RTSPROCESS_H
#define RTSPROCESS_H
//defining the rts process


#include <iostream>
#include <vector>
#include <string>
//include the necessary parts

using namespace std;

//create the rts process class itself, declare all necessary variables
class rtsProcess {
	protected:
	public:
		int pid;
		int burst;
		int arrival;
		int timeRemaining;
		int doneWaiting;
		int finishTime;
		int deadline;
		bool failed;

		//assign base values to all necessary variables
		rtsProcess() {
			this->failed = false;
			this->pid = 0;
			this->burst = 0;
			this->arrival = 0;
			this->timeRemaining =0;
			this->doneWaiting = 0;
			this->finishTime = 0;
			this->deadline = 0;
		};

		//set case where variables assigned by user
		rtsProcess (int pid, int burst, int arrival, int deadline) {
			this->pid = pid;
			this->burst = burst;
			this->arrival = arrival;
			this->timeRemaining = burst;
			this->deadline = deadline;
			this->doneWaiting = 0;
			this->finishTime = 0;
			this->failed = false;
		};
		~rtsProcess() {

		};
		//set case where input from file
		rtsProcess( const rtsProcess &p) {
			pid = p.pid;
			burst = p.burst;
			arrival = p.arrival;
			timeRemaining = p.timeRemaining;
			deadline = p.deadline;
			doneWaiting = p.doneWaiting;
			finishTime = p.finishTime;
			failed = p.failed;
		};
		// set with return
		rtsProcess& operator = (const rtsProcess &p) {
			pid = p.pid;
			burst = p.burst;
			arrival = p.arrival;
			timeRemaining = p.timeRemaining;
			deadline = p.deadline;
			doneWaiting = p.doneWaiting;
			finishTime = p.finishTime;
			failed = p.failed;
			return *this;
		};
		//set the operators
		bool operator== (const rtsProcess &p) {
			return (this->pid == p.pid && this->arrival == p.arrival && this->burst == p.burst);
		}
		bool operator!= (const rtsProcess &p){
			return !(this->pid == p.pid && this->arrival == p.arrival && this->burst == p.burst);
		}
		friend ostream& operator << (ostream &os, const rtsProcess &p) {
			p.display(os);
			return os;
		};
		//set the display to the console
		void display(ostream &os) const {
			os << "\t" << pid;
			os << "\t" << burst;
			os << "\t" << arrival;
			os << "\t" << deadline;
			os << "\t\t" << timeRemaining;
		};
};
#endif