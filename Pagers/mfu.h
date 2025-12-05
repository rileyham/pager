// FILE: mfu.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Header file for the Most Frequently Used paging algorithm
//
#ifndef MFU_H
#define MFU_H

#include <queue>
#include <string>
#include "../process.h"
using namespace std;

// Takes in a series of memory locations the number of frames and simulates MFU paging
// Ties are broken by choosing the least recently used page
// returns the number of page faults that occurred
int MFU(Process p, int pages, int frames);

#endif