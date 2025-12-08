// frameTable.h
//  Group 1: Chase Gartner, Ryan Geisler, Riley Ham
//  Operating Systems, Fall 2025
//
// FrameTable class implementation
//

#ifndef FRAMETABLE_H
#define FRAMETABLE_H

#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class FrameTable {
public:
    FrameTable(int totalFrames);
    ~FrameTable();

    // insetEntry
    // inserts a new entry into the frame table at the specified index
    bool insertEntry(int processId, int pageNumber, int frameIndex);

    // incrementUse
    // increments the use count and updates the last used time for a frame
    void incrementUse(int frameIndex);

    // getOldestEntryIndex
    // returns the index of the oldest entry in the frame table
    int getOldestEntryIndex();

    // getNewestEntryIndex
    // returns the index of the newest entry in the frame table
    int getNewestEntryIndex();

    // getMostUsedFrameIndex
    // returns the index of the most used frame in the frame table
    int getMostUsedFrameIndex() const;

    // getLeastUsedFrameIndex
    // returns the index of the least used frame in the frame table
    int getLeastUsedFrameIndex() const;

    // getFrameCount
    // returns the number of frames currently in use
    int getFrameCount() const;

    // contains
    // checks if a page for a given process is in the frame table
    bool contains(int processId, int pageNumber, int &frameIndex);

    // openSlot
    // checks if there is an open slot in the frame table
    bool openSlot(int &frameIndex);

    // setNewestEntryIndex
    // sets the newest entry index
    void setNewestEntryIndex(int index);

    // free
    // frees all frames associated with a given process ID
    void free(int processID);

    // getFifo
    // returns the index of the next frame to be replaced using FIFO
    int getFifo();

private:
    int totalFrames;
    int frameCount;
    int totalInstructions;
    queue<int> fifo;

    struct FrameTableEntry {
        int processId;  
        int pageNumber;
        int uses;
        int lastUsed;
        bool free;
    };

    vector<FrameTableEntry> frameTable;

};

#endif // FRAMETABLE_H