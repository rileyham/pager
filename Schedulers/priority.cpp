// FILE: priority.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Implementation of the priority scheduling algorithm, both preemptive and non-preemptive.
//

#include "priority.h"
#include <vector>
#include <iostream>
using namespace std;

void PriorityNonPreemptive(std::queue<Process> processes, bool isVerbose, string& response) {
    priority_queue<Process> readyQueue;
    int elapsedTime = 0;
    int numProcesses = processes.size();
    double totalWaitTime = 0;
    
    // Initially load processes that have already arrived
    for (int i = 0; i < numProcesses; ++i) {
        if (processes.front().getArrivalTime() <= elapsedTime) {
            readyQueue.push(processes.front());
            processes.pop();
        }
    }

    while (!readyQueue.empty() || !processes.empty()) {

        // if readyQueue is empty, we need to advance time
        if (readyQueue.empty()) {
            response += "CPU is idle at time " + to_string(elapsedTime) + "\n";
            elapsedTime++;
            // Load any new processes that have arrived
            while (!processes.empty() && processes.front().getArrivalTime() <= elapsedTime) {
                readyQueue.push(processes.front());
                processes.pop();
            }
        }

        else {
            Process currentProcess = readyQueue.top();
            readyQueue.pop();
            if (currentProcess.getArrivalTime() <= elapsedTime) {
                // Process finishes execution
                elapsedTime += currentProcess.getRemainingCpuBurst();
                int waitTime = elapsedTime - currentProcess.getArrivalTime() - currentProcess.getTotalCpuBurst();

                if (isVerbose) {
                    response += "P" + to_string(currentProcess.getId()) + " finished at time " + to_string(elapsedTime) + " ";
                    response += " Wait Time: " + to_string(waitTime) + "\n";
                }
                totalWaitTime += waitTime;
            }

            // Load any new processes that have arrived
            while (!processes.empty() && processes.front().getArrivalTime() <= elapsedTime) {
                readyQueue.push(processes.front());
                processes.pop();
            }
        }
    }
    if (isVerbose) response += "Elapsed Time: " + to_string(elapsedTime) + "\n";
    response += "The average wait time is " + to_string(totalWaitTime / numProcesses);
}

void PriorityPreemptive(queue<Process> processes, bool isVerbose, string& response) {
    priority_queue<Process> readyQueue;
    int elapsedTime = 0;
    int numProcesses = processes.size();
    double totalWaitTime = 0;
    
    // Initially load processes that have already arrived
    for (int i = 0; i < numProcesses; ++i) {
        if (processes.front().getArrivalTime() <= elapsedTime) {
            readyQueue.push(processes.front());
            processes.pop();
        }
    }

    while (!readyQueue.empty() || !processes.empty()) {

        // if readyQueue is empty, we need to advance time
        if (readyQueue.empty()) {
            response += "CPU is idle at time " + to_string(elapsedTime) + "\n";
            elapsedTime++;
            // Load any new processes that have arrived
            while (!processes.empty() && processes.front().getArrivalTime() <= elapsedTime) {
                readyQueue.push(processes.front());
                processes.pop();
            }
        }

        else {
            Process currentProcess = readyQueue.top();
            readyQueue.pop();
            if (currentProcess.getArrivalTime() <= elapsedTime) {
                // Process runs for 1 time unit
                elapsedTime += 1;
                currentProcess.decrementRemainingCpuBurst(1);

                // Check if process is finished
                if (currentProcess.getRemainingCpuBurst() == 0) {
                    int waitTime = elapsedTime - currentProcess.getArrivalTime() - currentProcess.getTotalCpuBurst();

                    if (isVerbose) {
                        response += "P" + to_string(currentProcess.getId()) + " finished at time " + to_string(elapsedTime) + " ";
                        response += " Wait Time: " + to_string(waitTime) + "\n";
                    }
                    totalWaitTime += waitTime;
                } else {
                    // Requeue the process if not finished
                    readyQueue.push(currentProcess);
                }
            }

            // Load any new processes that have arrived
            while (!processes.empty() && processes.front().getArrivalTime() <= elapsedTime) {
                readyQueue.push(processes.front());
                processes.pop();
            }
        }
    }
    if (isVerbose) response += "Elapsed Time: " + to_string(elapsedTime) + "\n";
    response += "The average wait time is " + to_string(totalWaitTime / numProcesses);
}