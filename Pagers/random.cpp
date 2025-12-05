// FILE: random.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//

#include "random.h"
#include <vector>
#include <cstdlib> 
using namespace std;

int Random(Process p, int frames) {
    int pageFaults = 0;

    if (frames <= 0) {
        return 0;
    }

    // -1 means the frame is empty
    vector<int> frameTable(frames, -1);
    int filled = 0; 

    while (p.hasNextInstruction()) {
        int page = p.getNextPage();
        bool hit = false;

        // check if page is already loaded in any frame
        for (int i = 0; i < frames; i++) {
            if (frameTable[i] == page) {
                hit = true;
                break;
            }
        }

        if (!hit) {
            pageFaults++;
            if (filled < frames) {
                //still have empty, use the next free slot
                frameTable[filled] = page;
                filled++;
            } else {
                // all frames full, pick a random frame index to replace
                int victim = rand() % frames;         
                while (victim >= frames) {     // bring it into [0, frames-1]
                    victim = victim - frames;
                }

                frameTable[victim] = page;
            }
        }
        p.executeNextInstruction();
    }
    return pageFaults;
}