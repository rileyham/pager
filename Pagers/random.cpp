// FILE: random.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//

#include "random.h"
#include <vector>
#include <cstdlib> 
using namespace std;

int Random(Process &p, int frames, FrameTable &ft, int instructionsToExecute) {
    int pageFaults = 0;

    if (frames <= 0) return 0;

    for (int i = 0; i < instructionsToExecute && p.hasNextInstruction(); i++) {

        int page = p.getNextPage();
        p.executeNextInstruction();

        int frameIndex = -1;

        // Check if page is already in a frame
        if (ft.contains(p.getId(), page, frameIndex)) {
            continue;
        }

        pageFaults++;

        if (ft.openSlot(frameIndex)) {
            ft.insertEntry(p.getId(), page, frameIndex);
        }
        else {
            int victim = rand() % frames;

            ft.insertEntry(p.getId(), page, victim);
        }
    }

    return pageFaults;
}
