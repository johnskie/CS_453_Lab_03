#ifndef PROCESS_H
#define PROCESS_H
class Process
{
public:
    int pid, burstTime, priority, arrivalTime, deadline;
    // io_ticks = length of IO io_end is when the IO would end
    int io_ticks, io_end;
    // burstRemaining is how much time is left for the process
    int burstRemaining;
    // the time at which the last process was ran
    int lastTime;
    Process();
    Process(int pid, int burst, int at, int priority, int deadline, int io);
    // getters
    int getPID();
    int getBurstTime();
    int getArrivalTime();
    int getPriority();
    int getDeadline();
    int getIO();
    int getLastTime();
    int getBurstRemaining();
    // other functions
    bool isComplete();
    void decrementTime();
    // setters
    void setLastTime(int t);
    void setPID(int t);
    void setBurstTime(int t);
    void setArrivalTime(int t);
    void setPriority(int t);
    void setDeadline(int t);
    void setIO(int t);
    void setBurstRemaining(int t);
	void toString();

};
#endif
