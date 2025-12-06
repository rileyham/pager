// FILE: roundRobin.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
//  Interface of the round robin scheduling algorithm.
//
#ifndef ROUNDROBIN_H
#define ROUNDROBIN_H

#include <string>
#include "../process.h"
#include <queue>
using namespace std;

// Takes in a queue of processes and a time quantum and simulates round robin scheduling
// result is placed in response string
void RoundRobin(std::queue<Process> processes, int timeQuantum, bool isVerbose, string& response);

#endif