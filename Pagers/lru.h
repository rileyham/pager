// FILE: lru.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Header file for the Least Recently Used paging algorithm
#ifndef LRU_H
#define LRU_H

#include <queue>
#include <string>
#include "../process.h"
#include "../frameTable.h"

using namespace std;

// Takes in a process, number of frames, frame table, and number of instructions to execute
// Simulates Least Recently Used paging
// returns number of page faults
int LRU(Process &p, int frames, FrameTable &ft, int instructionsToExecute);

#endif