// FILE: priority.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
//  Interface of the shortest job first scheduling algorithm.
//

#ifndef SJF_H
#define SJF_H

#include <string>
#include "../process.h"
#include <queue>
using namespace std;

// Takes in a queue of processes and simulates non-preemptive SJF scheduling
// Based on non-preemptive priority scheduling where priority is total CPU burst
// result is placed in response string
void SJFNonPreemptive(std::queue<Process> processes, bool isVerbose, string& response);

// Takes in a queue of processes and simulates preemptive SJF scheduling
// Based on preemptive priority scheduling where priority is total CPU burst
// result is placed in response string
void SJFPreemptive(std::queue<Process> processes, bool isVerbose, string& response);

#endif