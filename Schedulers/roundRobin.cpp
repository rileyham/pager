// FILE: roundRobin.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Implementation of the round robin scheduling algorithm.
//

#include "roundRobin.h"
#include <vector>
#include <iostream>
using namespace std;

void RoundRobin(std::queue<Process> processes, int timeQuantum, bool isVerbose, string& response) {
    queue<Process> readyQueue;
    int elapsedTime = 0;
    int numProcesses = processes.size();
    bool processCompleted = false;
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
            if (isVerbose) response += "CPU is idle at time " + to_string(elapsedTime) + "\n";
            elapsedTime++;
            // Load any new processes that have arrived
            while (!processes.empty() && processes.front().getArrivalTime() <= elapsedTime) {
                readyQueue.push(processes.front());
                processes.pop();
            }
        }

        else {
            Process currentProcess = readyQueue.front();
            readyQueue.pop();
            if (currentProcess.getArrivalTime() <= elapsedTime) {
                if(currentProcess.getRemainingCpuBurst() <= timeQuantum) {
                    // Process finishes execution this quantum
                    elapsedTime += currentProcess.getRemainingCpuBurst();
                    int waitTime = elapsedTime - currentProcess.getArrivalTime() - currentProcess.getTotalCpuBurst();

                    if (isVerbose) {
                        response += "P" + to_string(currentProcess.getId()) + " ran for " + to_string(currentProcess.getRemainingCpuBurst()) + " units." + "\n";
                        response += "P" + to_string(currentProcess.getId()) + " finished at time " + to_string(elapsedTime) + " ";
                        response += " Wait Time: " + to_string(waitTime) + "\n";
                    }
                    totalWaitTime += waitTime;

                    // Process is done, do not requeue
                    processCompleted = true;

                } else {
                    // Process does not finish, requeue it
                    elapsedTime += timeQuantum;
                    if (isVerbose) response += "P" + to_string(currentProcess.getId()) + " ran for " + to_string(timeQuantum) + " units." + "\n";
                    currentProcess.decrementRemainingCpuBurst(timeQuantum);
                }
            }

            while (!processes.empty() && processes.front().getArrivalTime() <= elapsedTime) {
                readyQueue.push(processes.front());
                processes.pop();
            }

            if (!processCompleted) {
                readyQueue.push(currentProcess);
            }
            processCompleted = false;
        }
    }

    if (isVerbose) response += "Elapsed Time: " + to_string(elapsedTime) + "\n";
    response += "The average wait time is " + to_string(totalWaitTime/numProcesses);
    return;

}