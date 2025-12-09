// FILE: fifo.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
#include "fifo.h"
#include <iostream>
#include <vector>
using namespace std;

int FIFO(Process &p, int frames, FrameTable &ft, int instructionsToExecute, string &response) {
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
            response += "PID:" + to_string(p.getId()) + " Page Hit: Page " + to_string(page) + " found in frame " + to_string(frameIndex) + "\n";
        } 
        else {
            pageFaults++;
            // Load page into an open slot if available
            if (ft.openSlot(frameIndex)) {
                ft.insertEntry(p.getId(), page, frameIndex);

                response += "PID:" + to_string(p.getId()) + " Page Fault: Loaded page " + to_string(page)  + " into frame " + to_string(frameIndex) + "\n";
            // No open slots, replace the first in 
            } else {
                int victimIndex = ft.getFifo();
                response += "PID:" + to_string(p.getId()) + " Page Fault: Replacing page " + to_string(page) + " to frame " + to_string(victimIndex) + "\n";
                ft.insertEntry(p.getId(), page, victimIndex);
            }
        }
        p.executeNextInstruction();  
    }
    return pageFaults;
}
