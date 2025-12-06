// FILE: fcfs.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Interface of the first-come, first-serve scheduling algorithm.
//

#ifndef FCFS_H
#define FCFS_H

#include <queue>
#include "../process.h"
#include <string>
using namespace std;

// Takes in a queue of processes and simulates FCFS scheduling
// result is placed in response string
void FCFS(queue<Process> ready, bool isVerbose, string &response);

#endif// FCFS_H
