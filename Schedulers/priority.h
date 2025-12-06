// FILE: priority.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
//  Interface of the priority scheduling algorithm.
//

#ifndef PRIORITY_H
#define PRIORITY_H

#include <string>
#include "../process.h"
#include <queue>
using namespace std;

// Takes in a queue of processes and simulates non-preemptive priority scheduling
// result is placed in response string
// Higher priority value means lower priority
void PriorityNonPreemptive(std::queue<Process> processes, bool isVerbose, string& response);

// Takes in a queue of processes and simulates preemptive priority scheduling
// result is placed in response string
// Higher priority value means lower priority
void PriorityPreemptive(std::queue<Process> processes, bool isVerbose, string& response);

#endif

