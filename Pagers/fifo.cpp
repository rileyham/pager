// FILE: fifo.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
#include "fifo.h"
#include <vector>
using namespace std;

int FIFO(Process p, int frames) {
    int pageFaults = 0;
    if (frames <= 0) return 0;

    vector<int> frameTable;
    int nextToReplace = 0;

    while (p.hasNextInstruction()) {
        int page = p.getNextPage();
        bool hit = false;
        for (int i = 0; i < frameTable.size(); i++) {
            if (frameTable[i] == page) {
                hit = true;
                break;
    }
}
        if (!hit) {
            pageFaults++;

            if ((int)frameTable.size() < frames) {
                frameTable.push_back(page);
            } else {
                //replace the oldest page
                frameTable[nextToReplace] = page;
                nextToReplace++;
                if (nextToReplace == frames) {
                    nextToReplace = 0;  // wrap back to frame 0
                }

            }
        }
        p.executeNextInstruction();
    }

    return pageFaults;
}
