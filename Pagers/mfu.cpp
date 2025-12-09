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

int MFU(Process &p, int frames, FrameTable &ft, int instructionsToExecute, string &response) {
    int pageFaults = 0;
    bool debug = false;

    for (int i = 0; i < instructionsToExecute; ++i) {
        int currentPage = p.getNextPage();
        p.executeNextInstruction();

        int frameIndex = -1;

        // check if page is already in a frame
        if (ft.contains(p.getId(), currentPage, frameIndex)) {
            ft.incrementUse(frameIndex);
            response += "PID:" + to_string(p.getId()) + " Page Hit: Page " + to_string(currentPage) + " found in frame " + to_string(frameIndex) + "\n";

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
            response += "PID:" + to_string(p.getId()) + " Page Fault: Loaded page " + to_string(currentPage)  + " into frame " + to_string(frameIndex) + "\n";

        // no open slots, replace the most frequently used page
        } else {
            int victimIndex = ft.getMostUsedFrameIndex();
            if (debug) {
                cout << "Page: " << currentPage << ", PID:" << p.getId() << " replacing page in frame " << victimIndex << endl;
            }
            response += "PID:" + to_string(p.getId()) + " Page Fault: Replacing page " + to_string(currentPage) + " to frame " + to_string(victimIndex) + "\n";
            ft.insertEntry(p.getId(), currentPage, victimIndex);
        }
    }

    return pageFaults;
}
