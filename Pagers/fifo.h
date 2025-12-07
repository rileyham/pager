// FILE: fifo.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//

#ifndef FIFO_H
#define FIFO_H

#include "../process.h"
#include "../frameTable.h"


// Simulate FIFO page replacement for a single process
// Returns the number of page faults for that process
int FIFO(Process &p, int frames, FrameTable &ft , int instructionsToExecute);

#endif
