// FILE: mfu.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Implementation of the Least Recently Used Paging Algorithm
//
#include "mfu.h"
#include <queue>
#include <set>
#include <iostream>
using namespace std;

int MFU(Process &p, int frames, FrameTable &ft, int instructionsToExecute) {
    int pageFaults = 0;
    bool debug = false;

    for (int i = 0; i < instructionsToExecute; ++i) {
        int currentPage = p.getNextPage();
        p.executeNextInstruction();

        int frameIndex = -1;

        // check if page is already in a frame
        if (ft.contains(p.getId(), currentPage, frameIndex)) {
            ft.incrementUse(frameIndex);

            if (debug) {
                cout << "Page: " << currentPage << ", PID:" << p.getId() << " found in frame " << frameIndex << endl;
            }
            continue;
        }

        pageFaults++;

        // load page into an open slot if available
        if (ft.openSlot(frameIndex)) {
            ft.insertEntry(p.getId(), currentPage, frameIndex);
            if (debug) {
                cout  << "Page: " << currentPage << ", PID:" << p.getId() << " loaded into empty frame " << frameIndex << endl;
            }

        // no open slots, replace the most frequently used page
        } else {
            int victimIndex = ft.getMostUsedFrameIndex();
            if (debug) {
                cout << "Page: " << currentPage << ", PID:" << p.getId() << " replacing page in frame " << victimIndex << endl;
            }
            ft.insertEntry(p.getId(), currentPage, victimIndex);
        }
    }

    return pageFaults;
}
