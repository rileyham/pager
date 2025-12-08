// frameTable.cpp

#include "frameTable.h"

FrameTable::FrameTable(int totalFrames){
    frameCount = 0;          // frames currently used
    totalInstructions = 0;
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

    for (int i = 0; i < frameCount; ++i){
        cout
             << ", Page " << frameTable[i].pageNumber 
             << ", Uses " << frameTable[i].uses 
             << ", Last Used " << frameTable[i].lastUsed 
             << " / ";
    }
    cout << endl;

    return true;
}


int FrameTable::getFrameCount() const{
    return frameCount;
}

int FrameTable::getOldestEntryIndex(){
    int oldestIndex = 0;
    int mostRecentInstruction = 10000000;
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
    int newestIndex = 0;
    int mostRecentInstruction = -1;
    bool foundFreeSlot = false;
    for(int i = 0; i < frameCount; ++i){
        if(frameTable[i].free && frameTable[i].lastUsed > mostRecentInstruction){
            newestIndex = i;
            mostRecentInstruction = frameTable[i].lastUsed;
            foundFreeSlot = true;
        }
    }
    if(foundFreeSlot) return newestIndex;

    for(int i = 0; i < frameCount; ++i){
        if(frameTable[i].lastUsed > mostRecentInstruction){
            newestIndex = i;
            mostRecentInstruction = frameTable[i].lastUsed;
        }
    }

    return newestIndex;
}

int FrameTable::getMostUsedFrameIndex() const{
    int maxUses = -1;
    int frameIndex = -1;
    bool foundFreeSlot = false;

    for(int i = 0; i < frameCount; ++i){
        if(frameTable[i].free && frameTable[i].uses >= maxUses){
            if(frameTable[i].uses == maxUses){
                if(!frameIndex && frameTable[i].lastUsed < frameTable[frameIndex].lastUsed){
                    maxUses = frameTable[i].lastUsed;
                    foundFreeSlot = true;
                    frameIndex = i;
                }
            }
        }
    }
    if(foundFreeSlot) return frameIndex;

    for(int i = 0; i < frameCount; ++i){
        if(frameTable[i].uses >= maxUses){
            if(frameTable[i].uses == maxUses){
                if(!frameIndex && frameTable[i].lastUsed < frameTable[frameIndex].lastUsed){
                    maxUses = frameTable[i].lastUsed;
                    frameIndex = i;
                }
            }
        }
    }
    return frameIndex;
}

int FrameTable::getLeastUsedFrameIndex() const{
    int minUses = 10000000;
    int frameIndex = -1;
    bool foundFreeSlot = false;

    for(int i = 0; i < frameCount; ++i){
        if(frameTable[i].free && frameTable[i].uses <= minUses){
            if(frameTable[i].uses == minUses){
                if(!frameIndex && frameTable[i].lastUsed < frameTable[frameIndex].lastUsed){
                    minUses = frameTable[i].lastUsed;
                    foundFreeSlot = true;
                    frameIndex = i;

                }
            }
        }
    }
    if(foundFreeSlot) return frameIndex;

    for(int i = 0; i < frameCount; ++i){
        if(frameTable[i].uses <= minUses){
            if(frameTable[i].uses == minUses){
                if(!frameIndex && frameTable[i].lastUsed < frameTable[frameIndex].lastUsed){
                    minUses = frameTable[i].lastUsed;
                    frameIndex = i;
                }
            }
        }
    }
    return frameIndex;
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