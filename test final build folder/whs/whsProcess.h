#ifndef WHSPROCESS_H
#define WHSPROCESS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class whsProcess {
	protected:
		int pid;
	
	public:
		int burst;
		int arrival;
		int timeRemaining;
		int doneWaiting;
		int finishTime;
		int priority;
		int originalpriority;
		int agefactor;
		int age;
		int IO;

		whsProcess() {
			this->pid = 0;
			this->burst = 0;
			this->arrival = 0;
			this->timeRemaining =0;
			this->doneWaiting = 0;
			this->finishTime = 0;
			this->priority = 0;
			this->agefactor = 5;
			this->age = 0;
			this->IO = 0;
		};
		whsProcess(int pid, int burst, int arrival, int priority, int agefactor, int IO) {
			this->pid = pid;
			this->burst = burst;
			this->arrival = arrival;
			this->timeRemaining = burst;
			this->priority = priority;
			this->originalpriority = priority;
			this->doneWaiting = 0;
			this->finishTime = 0;
			this->agefactor = agefactor;
			this->age = 0;
			this->IO = IO;
		};
		~whsProcess() {
			
		};
		whsProcess( const whsProcess &p) {
			//cout << "p being copied from" << endl << p << endl; 
			pid = p.getPid();
			burst = p.burst;
			arrival = p.arrival;
			timeRemaining = p.timeRemaining;
			priority = p.priority;
			originalpriority = p.originalpriority;
			doneWaiting = p.doneWaiting;
			age = p.age;
			agefactor = p.agefactor;
			finishTime = p.finishTime;
			IO = p.IO;
		};
		whsProcess& operator= (const whsProcess &p){
			pid = p.getPid();
			age = p.age;
			agefactor = p.agefactor;
			burst = p.burst;
			arrival = p.arrival;
			timeRemaining = p.timeRemaining;
			priority = p.priority;
			originalpriority = p.originalpriority;
			doneWaiting = p.doneWaiting;
			finishTime = p.finishTime;
			IO = p.IO;
			return *this;
		};
		bool operator== (const whsProcess &p) {
			return (this->pid==p.getPid() && this->arrival == p.arrival && this->burst == p.burst);
		};
		bool operator!= (const whsProcess &p){
			return !(this->pid==p.getPid() && this->arrival == p.arrival && this->burst == p.burst);
		};
		friend ostream& operator<< (ostream &os, const whsProcess &p) {
			p.display(os);
			return os;
		};
		void display(ostream &os) const {
			os << "\t" << getPid();
			os << "\t" << burst;
			os << "\t" << arrival;
			os << "\t" << age;
			os << "\t\t" << timeRemaining;
		};
		void AGE(){
			this->age++;
		};
		bool aged(){
			return (age >= agefactor);
		};
		int getPid() const{
			return this->pid;
		};

};
#endif