// FILE: process.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
//  Interface of the process class.
//
// Overloaded operators for priority queue: https://learn.microsoft.com/en-us/troubleshoot/developer/visualstudio/cpp/libraries/stl-priority-queue-class-custom-type
#ifndef PROCESS_H
#define PROCESS_H

class Process {
public:
    Process(int ID, int Arrival_Time, int Total_CPU_Burst, int Priority);
    Process(int ID);
    int getId() const;
    int getArrivalTime() const;
    int getTotalCpuBurst() const;
    int getPriority() const;
    int getRemainingCpuBurst() const;
    void updatePrioirity(int newPriority);
    void decrementRemainingCpuBurst(int burst) { remainingCPUBurst -= burst; }
    bool operator<(const Process& other) const {
        // Higher priority value means lower priority
        if (this->priority == other.priority) {
            return this->id > other.id; // Earlier arrival time has higher priority
        }

        return this->priority > other.priority;
    }

private:
    int id;
    int arrivalTime;
    int totalCpuBurst;
    int remainingCPUBurst;
    int priority;
};

#endif
