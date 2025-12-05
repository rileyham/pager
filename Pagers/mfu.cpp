// FILE: mfu.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Implementation of the Most Frequently Used Paging Algorithm
//
#include "mfu.h"
#include <queue>
#include <set>
#include <iostream>
using namespace std;

int MFU(Process p, int pages, int frameCount) {
    queue<int> recentFrames;
    int numberOfPages = p.getTotalPages();
    int usedFrames = 0;
    int pageFaults = 0;
    int currentFrame;
    bool pageExists = false;
    bool debug = true;
    int pageUses[pages];
    int frames[frameCount];
    for (int i = 0; i < pages; ++i) {
        pageUses[i] = 0;
    }

    for (int i = 0; i < numberOfPages; ++i) {
        int currentPage = p.getNextPage();
        p.executeNextInstruction();
        pageExists = false;

        // is the page already loaded?
        for (int j = 0; j < usedFrames; ++j) {
            if (frames[j] == currentPage) {
                recentFrames.pop();
                currentFrame = j;
                pageExists = true;
            }
            else {
                recentFrames.push(recentFrames.front());
                recentFrames.pop();
            }
        }
        if (pageExists) {
            recentFrames.push(currentPage);
            pageUses[frames[currentFrame]]++;
            if (debug) {
                cout << "Page " << currentPage << " is already in a frame. Current Frames:";
                for(int j = 0; j < usedFrames; ++j) {
                    cout << " " << frames[j] << "[" << pageUses[frames[j]] << "]";
                }
                cout << endl;
            }
            continue;
        }

        // are there available frames?
        if (usedFrames < frameCount) {
            frames[usedFrames] = currentPage;
            pageUses[currentPage]++;
            recentFrames.push(currentPage);
            usedFrames++;
            pageFaults++;

            if (debug) {
                cout << "Page " << currentPage << " loaded. Current Frames:";
                for(int j = 0; j < usedFrames; ++j) {
                    cout << " " << frames[j] << "[" << pageUses[frames[j]] << "]";
                }
                cout << endl;
            }
        } 

        else {
            // frames are full, find a victim
            int victimFrame = 0;
            int maxUses = -1;
            for (int j = 0; j < usedFrames; ++j) {
                if (pageUses[frames[j]] > maxUses) {
                    maxUses = pageUses[frames[j]];
                    victimFrame = j;
                }
                if (pageUses[frames[j]] == maxUses) {
                    // tie breaker: least recently used
                    queue<int> tempQueue = recentFrames;
                    while (!tempQueue.empty()) {
                        if (tempQueue.front() == frames[j]) {
                            victimFrame = j;
                            break;
                        }
                        if (tempQueue.front() == frames[victimFrame]) {
                            break;
                        }
                        tempQueue.pop();
                    }
                }
            }   
            int victimPage = frames[victimFrame];
            frames[victimFrame] = currentPage;
            pageUses[currentPage]++;
            pageFaults++;

            if (debug) {
                cout << "Page " << currentPage << " replaced " << victimPage << " Current Frames:";
                for(int j = 0; j < usedFrames; ++j) {
                    cout << " " << frames[j] << "[" << pageUses[frames[j]] << "]";
                }
                cout << endl;
            }
        }
  
    }

    return pageFaults;
}