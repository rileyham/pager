// frameTable.h

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

    bool insertEntry(int processId, int pageNumber, int frameIndex);
    void incrementUse(int frameIndex);
    int getOldestEntryIndex();
    int getNewestEntryIndex();
    int getMostUsedFrameIndex() const;
    int getLeastUsedFrameIndex() const;
    int getFrameCount() const;
    bool contains(int processId, int pageNumber, int &frameIndex);
    bool openSlot(int &frameIndex);
    void setNewestEntryIndex(int index);
    void free(int processID);
    void updateFreeFrames(int PID);
    int getFifo();

private:
    int totalFrames;
    int frameCount;
    int totalInstructions;
    queue<int> fifo;

    struct FrameTableEntry {
        int processId;     // ID of the process owning this frame
        int pageNumber;
        int uses;
        int lastUsed;
        bool free;
    };

    vector<FrameTableEntry> frameTable;

};

#endif // FRAMETABLE_H