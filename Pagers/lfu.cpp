// FILE: lfu.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Implementation of the Least Recently Used Paging Algorithm
//
#include "lfu.h"
#include <queue>
#include <set>
#include <iostream>
using namespace std;

int LFU(Process &p, int frames, FrameTable &ft, int instructionsToExecute) {
    int pageFaults = 0;
    bool debug = false;

    for (int i = 0; i < instructionsToExecute; ++i) {
        int currentPage = p.getNextPage();
        p.executeNextInstruction();

        int frameIndex = -1;

        if (ft.contains(p.getId(), currentPage, frameIndex)) {
            // Page is already in a frame, just increment usage
            ft.incrementUse(frameIndex);

            if (debug) {
                cout << "Page: " << currentPage << ", PID:" << p.getId() << " found in frame " << frameIndex << endl;
            }
            continue;
        }

        // Page not found → page fault
        pageFaults++;

        if (ft.openSlot(frameIndex)) {
            // There is an empty frame
            ft.insertEntry(p.getId(), currentPage, frameIndex);
            if (debug) {
                cout  << "Page: " << currentPage << ", PID:" << p.getId() << " loaded into empty frame " << frameIndex << endl;
            }
        } else {
            // No empty frame → replace least recently used
            int victimIndex = ft.getLeastUsedFrameIndex();
            if (debug) {
                cout << "Page: " << currentPage << ", PID:" << p.getId() << " replacing page in frame " << victimIndex << endl;
            }
            ft.insertEntry(p.getId(), currentPage, victimIndex);
        }
    }

    return pageFaults;
}
