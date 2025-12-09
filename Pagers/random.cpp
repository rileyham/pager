// FILE: random.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//

#include "random.h"
#include <vector>
#include <cstdlib> 
using namespace std;

int Random(Process &p, int frames, FrameTable &ft, int instructionsToExecute, string &response) {
    srand(time(0));
    int pageFaults = 0;

    if (frames <= 0) return 0;

    for (int i = 0; i < instructionsToExecute && p.hasNextInstruction(); i++) {

        int page = p.getNextPage();
        p.executeNextInstruction();

        int frameIndex = -1;

        // Check if page is already in a frame
        if (ft.contains(p.getId(), page, frameIndex)) {
            ft.incrementUse(frameIndex);
            response += "PID:" + to_string(p.getId()) + " Page Hit: Page " + to_string(page) + " found in frame " + to_string(frameIndex) + "\n";
            continue;
        }

        pageFaults++;

        // Load page into an open slot if available
        if (ft.openSlot(frameIndex)) {
            ft.insertEntry(p.getId(), page, frameIndex);
            response += "PID:" + to_string(p.getId()) + " Page Fault: Loaded page " + to_string(page)  + " into frame " + to_string(frameIndex) + "\n";
        }
        // No open slots, replace a random page
        else {
            int victim = rand() % frames;

            ft.insertEntry(p.getId(), page, victim);
            response += "PID:" + to_string(p.getId()) + " Page Fault: Replacing page " + to_string(page) + " to frame " + to_string(victim) + "\n";           
        }
    }

    return pageFaults;
}
