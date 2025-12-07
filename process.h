// FILE: process.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
//  Interface of the process class.
//
// Overloaded operators for priority queue: https://learn.microsoft.com/en-us/troubleshoot/developer/visualstudio/cpp/libraries/stl-priority-queue-class-custom-type

#ifndef PROCESS_H
#define PROCESS_H

#include <queue>

using namespace std;


class Process {
public:
    Process(int ID, int Arrival_Time, int Total_CPU_Burst, int Priority);
    Process(int ID);
    Process();
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
    bool insertNextInstruction(int memoryLocation, int pageNumber);
    int getNextPage();
    bool executeNextInstruction();
    void printDEBUG();
    bool hasNextInstruction(); 
    int getTotalPages();
    void setTotalInstructions();
    int getTotalInstructions();

private:
    struct MemoryLocation {
        int memoryLocation;
        int pageNumber;
    };
    struct PageTableEntry {
        int pageNumber;
        bool validBit;
        int frameNumber;
    };

    int id;
    int arrivalTime;
    int totalCpuBurst;
    int remainingCPUBurst;
    int priority;
    int totalInstructions;
    queue <MemoryLocation> instructionSequence;
};

struct ProcessRunTime {
    int processID;
    int runTime;
};

#endif
