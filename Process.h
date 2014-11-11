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
    Process(int pid, int burst, int at, int priority, int deadline, int io);
    // getters
    int getPID();
    int getBurstTime();
    int getArrivalTime();
    int getPriority();
    int getDeadline();
    int getIO();
    int getLastTime();
    // other functions
    bool isComplete();
    void decrementTime();
    void setLastTime(int t);

};
#endif
