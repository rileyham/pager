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

// Takes in a series of memory locations and the number of frames simulates LRU paging
// returns the number of page faults that occurred
int LRU(Process &p, int frames, FrameTable &ft, int instructionsToExecute);

#endif