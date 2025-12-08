// FILE: fifo.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
#include "fifo.h"
#include <iostream>
#include <vector>
using namespace std;

int FIFO(Process &p, int frames, FrameTable &ft, int instructionsToExecute) {
    int pageFaults = 0;
    if (frames <= 0) return 0;

    int nextToReplace = 0;

    for (int instr = 0; instr < instructionsToExecute; instr++) {
        int page = p.getNextPage();
        bool hit = false;
        int frameIndex = -1;

        // Check if page is already in a frame
        if (ft.getFrameCount() != 0 && ft.contains(p.getId(), page, frameIndex)) {
            hit = true;
            ft.incrementUse(frameIndex);
        } 
        else {
            pageFaults++;
            // Load page into an open slot if available
            if (ft.openSlot(frameIndex)) {
                ft.insertEntry(p.getId(), page, frameIndex);
            // No open slots, replace the first in 
            } else {
                int victimIndex = ft.getFifo();
                ft.insertEntry(p.getId(), page, victimIndex);
            }
        }
        p.executeNextInstruction();  
    }
    return pageFaults;
}
