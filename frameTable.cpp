// frameTable.cpp

#include "frameTable.h"
#include <iostream>

FrameTable::FrameTable(int totalFrames){
    frameCount = 0;
    totalInstructions = 0;
    frameTable.resize(totalFrames);

}

FrameTable::~FrameTable(){
}

bool FrameTable::contains(int processId, int pageNumber, int &frameIndex){
    for(int i = 0; i < frameCount; i++){
        if(frameTable[i].processId == processId && frameTable[i].pageNumber == pageNumber){
            frameIndex = i;
            return true;
        }
    }
    return false;
}

bool FrameTable::openSlot(int &frameIndex){
    if (frameCount < frameTable.size()) {
        frameIndex = frameCount;
        return true;
    }
    return false;
}

bool FrameTable::insertEntry(int processId, int pageNumber, int frameIndex){
    totalInstructions++;
    frameTable[frameIndex].processId = processId;
    frameTable[frameIndex].pageNumber = pageNumber;
    frameTable[frameIndex].uses = 1;
    frameTable[frameIndex].lastUsed = totalInstructions;
    frameTable[frameIndex].free = false;

    if (frameCount < frameTable.size()){
        frameCount++;
    }
    fifo.push(frameIndex);

    return true;
}


int FrameTable::getFrameCount() const{
    return frameCount;
}

int FrameTable::getOldestEntryIndex(){
    int oldestIndex = 0;
    int mostRecentInstruction = 1000000;
    bool foundFreeSlot = false;
    for(int i = 0; i < frameCount; ++i){
        if(frameTable[i].free && frameTable[i].lastUsed < mostRecentInstruction){
            oldestIndex = i;
            mostRecentInstruction = frameTable[i].lastUsed;
            foundFreeSlot = true;
        }
    }
    if(foundFreeSlot) return oldestIndex;

    for(int i = 0; i < frameCount; ++i){
        if(frameTable[i].lastUsed < mostRecentInstruction){
            oldestIndex = i;
            mostRecentInstruction = frameTable[i].lastUsed;
        }
    }

    return oldestIndex;
}

int FrameTable::getNewestEntryIndex(){
    int newestIndex = 1000000;
    int mostRecenterInstruction = -1;
    bool foundFreeSlot = false;
    for(int i = 0; i < frameCount; ++i){
        if(frameTable[i].free && frameTable[i].lastUsed > mostRecenterInstruction){
            newestIndex = i;
            mostRecenterInstruction = frameTable[i].lastUsed;
            foundFreeSlot = true;
        }
    }
    if(foundFreeSlot) return newestIndex;

    for(int i = 0; i < frameCount; ++i){
        if(frameTable[i].lastUsed > mostRecenterInstruction){
            newestIndex = i;
            mostRecenterInstruction = frameTable[i].lastUsed;
        }
    }

    return newestIndex;
}

int FrameTable::getMostUsedFrameIndex() const {
    int victim = -1;
    int maxUses = -1;

    // Check free frames first
    for (int i = 0; i < frameCount; ++i) {
        if (frameTable[i].free) {
            if (frameTable[i].uses > maxUses ||
               (frameTable[i].uses == maxUses && frameTable[i].lastUsed < frameTable[victim].lastUsed)) {
                maxUses = frameTable[i].uses;
                victim = i;
            }
        }
    }
    if (victim != -1) return victim;

    // Otherwise choose overall most used
    maxUses = -1;
    for (int i = 0; i < frameCount; ++i) {
        if (frameTable[i].uses > maxUses ||
           (frameTable[i].uses == maxUses && frameTable[i].lastUsed < frameTable[victim].lastUsed)) {
            maxUses = frameTable[i].uses;
            victim = i;
        }
    }

    return victim;
}


int FrameTable::getLeastUsedFrameIndex() const {
    int victim = -1;
    int minUses = 10000000;

    // Check free frames first
    for (int i = 0; i < frameCount; ++i) {
        if (frameTable[i].free) {
            if (frameTable[i].uses < minUses ||
               (frameTable[i].uses == minUses && frameTable[i].lastUsed < frameTable[victim].lastUsed)) {
                minUses = frameTable[i].uses;
                victim = i;
            }
        }
    }
    if (victim != -1) return victim;

    // Otherwise choose overall least used
    minUses = 100000;
    for (int i = 0; i < frameCount; ++i) {
        if (frameTable[i].uses < minUses ||
           (frameTable[i].uses == minUses && frameTable[i].lastUsed < frameTable[victim].lastUsed)) {
            minUses = frameTable[i].uses;
            victim = i;
        }
    }

    return victim;
}

void FrameTable::incrementUse(int frameIndex){
    ++totalInstructions;
    frameTable[frameIndex].lastUsed = totalInstructions;
    frameTable[frameIndex].uses += 1;

}

void FrameTable::free(int processID){
    for(int i = 0; i < frameCount; ++i){
        if(frameTable[i].processId == processID){
            frameTable[i].free = true;
        }
    }
}

int FrameTable::getFifo(){
    int index = fifo.front();
    fifo.pop();
    return index;
}