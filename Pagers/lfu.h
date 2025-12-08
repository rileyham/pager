// FILE: lfu.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
#ifndef LFU_H
#define LFU_H

#include "../process.h"

// Least Frequently Used page replacement.
// Returns the number of page faults.
int LFU(Process p, int frames);

#endif
