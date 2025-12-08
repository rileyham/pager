// FILE: random.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//

#ifndef RANDOM_H
#define RANDOM_H

#include "../process.h"
#include "../frameTable.h"

// Takes in a process, number of frames, frame table, and number of instructions to execute
// Simulates Random paging
// returns number of page faults
int Random(Process &p, int frames, FrameTable &ft, int instructionsToExecute);

#endif