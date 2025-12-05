// FILE: random.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//

#ifndef RANDOM_H
#define RANDOM_H

#include "../process.h"

// Random page replacement for a single process
// Returns number of page faults
int Random(Process p, int frames);

#endif