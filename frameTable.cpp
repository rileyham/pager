// frameTable.cpp

#include "frameTable.h"

FrameTable::FrameTable(int totalFrames){
    frameCount = 0;          // frames currently used
    oldestEntryIndex = 0;
    newestEntryIndex = -1;
    frameTable.resize(totalFrames); // total number of frames
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
        frameCount++;
        return true;
    }
    return false;
}



bool FrameTable::insertEntry(int processId, int pageNumber, int frameIndex){
    frameTable[frameIndex].processId = processId;
    frameTable[frameIndex].pageNumber = pageNumber;
    frameTable[frameIndex].uses = 1;

    if (frameIndex < frameCount) { 
        oldestEntryIndex = (oldestEntryIndex + 1) % frameCount;
    }
    newestEntryIndex = frameIndex;

    return true;
}



int FrameTable::getFrameCount() const{
    return frameCount;
}

int FrameTable::getOldestEntryIndex(){
    int index = oldestEntryIndex;
    oldestEntryIndex = (oldestEntryIndex + 1) % frameCount;
    return index;
}

int FrameTable::getNewestEntryIndex(){
    return newestEntryIndex;
}

int FrameTable::getMostUsedFrameIndex() const{
    int maxUses = -1;
    int frameIndex = -1;

    for(int i = 0; i < frameCount; i++){
        if(frameTable[i].uses > maxUses){
            maxUses = frameTable[i].uses;
            frameIndex = i;
        }
    }
    return frameIndex;
}

int FrameTable::getLeastUsedFrameIndex() const{
    int minUses = 1000000;
    int frameIndex = -1;

    for(int i = 0; i < frameCount; i++){
        if(frameTable[i].uses < minUses){
            minUses = frameTable[i].uses;
            frameIndex = i;
        }
    }
    return frameIndex;
}


void FrameTable::incrementUse(int frameIndex){
    frameTable[frameIndex].uses += 1;

}

void FrameTable::setNewestEntryIndex(int index){
    newestEntryIndex = index;
}

void FrameTable::updateFreeFrames(int PID){
    for(int i = 0; i < frameCount; i++){
        if(frameTable[i].processId == PID){
            frameTable[i].free = 1;
        }
    }
}