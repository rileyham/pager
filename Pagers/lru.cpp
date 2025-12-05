// FILE: lru.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Implementation of the Least Recently Used Paging Algorithm
//
#include "lru.h"
#include <queue>
#include <set>
#include <iostream>
using namespace std;

int LRU(Process p, int frames) {
    queue<int> recentFrames;
    int totalPages = p.getTotalPages();
    int usedFrames = 0;
    int pageFaults = 0;
    int foundPage;
    bool pageExists = false;
    bool debug = true;

    for (int i = 0; i  < totalPages; ++i) {
        int currentPage = p.getNextPage();
        p.executeNextInstruction();
        pageExists = false;

        // is the page already loaded?
        for (int j = 0; j < usedFrames; ++j) {
            if (recentFrames.front() == currentPage) {
                recentFrames.pop();
                foundPage = currentPage;
                pageExists = true;
            }
            else {
                recentFrames.push(recentFrames.front());
                recentFrames.pop();
            }
        }
        if (pageExists) {
            recentFrames.push(foundPage);
            if (debug) {
                cout << "Page " << currentPage << " Found. Current Frames:";
                queue<int> tempFrames = recentFrames;
                while (!tempFrames.empty()) {
                    cout << " " << tempFrames.front();
                    tempFrames.pop();
                }
                cout << endl;
            }
            continue;
        }

        // are there available frames?
        if (usedFrames < frames) {

            recentFrames.push(currentPage);
            usedFrames++;
            pageFaults++;

            if (debug) {
                cout << "Page " << currentPage << " loaded. Current Frames:";
                queue<int> tempFrames = recentFrames;
                while (!tempFrames.empty()) {
                    cout << " " << tempFrames.front();
                    tempFrames.pop();
                }
                cout << endl;
            }
        } 

        // frames are full, find a victim
        else {
            int victimPage = recentFrames.front();
            recentFrames.pop();
            recentFrames.push(currentPage);
            pageFaults++;

            if (debug) {
                cout << "Page " << victimPage << " killed for " << currentPage << " Current Frames:";
                queue<int> tempFrames = recentFrames;
                while (!tempFrames.empty()) {
                    cout << " " << tempFrames.front();
                    tempFrames.pop();
                }
                cout << endl;
            }
        }
  
    }

    return pageFaults;
}