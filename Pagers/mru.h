// FILE: mru.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Header file for the Least Recently Used paging algorithm
#ifndef MRU_H
#define MRU_H

#include <queue>
#include <string>
#include "../process.h"
#include "../frameTable.h"

using namespace std;

// Takes in a process, number of frames, frame table, and number of instructions to execute
// Simulates Most Recently Used paging
// returns number of page faults
int MRU(Process &p, int frames, FrameTable &ft, int instructionsToExecute, string &response);

#endif