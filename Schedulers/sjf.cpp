// FILE: priority.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
//  Implementation of the shortest job first scheduling algorithm, both preemptive and non-preemptive.
//

#include "priority.h"
#include "sjf.h"
#include <vector>
#include <iostream>
using namespace std;

void SJFNonPreemptive(queue<Process> processes, bool isVerbose, string& response) {

    // create a new queue that uses totalCpuBurst as priority, allowing the same logic as priority scheduling
    queue<Process> burstPriorityQueue;
    int numProcesses = processes.size();
    for (int i = 0; i < numProcesses; ++i) {
        Process current = processes.front();
        current.updatePrioirity(current.getTotalCpuBurst());
        burstPriorityQueue.push(current);
        processes.pop();
    }
    PriorityNonPreemptive(burstPriorityQueue, isVerbose, response);
}

void SJFPreemptive(queue<Process> processes, bool isVerbose, string& response) {

    // create a new queue that uses totalCpuBurst as priority, allowing the same logic as priority scheduling
    queue<Process> burstPriorityQueue;
    int numProcesses = processes.size();
    for (int i = 0; i < numProcesses; ++i) {
        Process current = processes.front();
        current.updatePrioirity(current.getTotalCpuBurst());
        burstPriorityQueue.push(current);
        processes.pop();
    }
    PriorityPreemptive(burstPriorityQueue, isVerbose, response);
}