// FILE: process.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
//  Implementation of the Process class.
//
#include "process.h"
#include <iostream>
#include <string>

using namespace std;

Process::Process(int ID, int Arrival_Time, int Total_CPU_Burst, int Priority)
    : id(ID), arrivalTime(Arrival_Time), totalCpuBurst(Total_CPU_Burst), priority(Priority), remainingCPUBurst(Total_CPU_Burst) {}

Process::Process(int ID)
    : id(ID), arrivalTime(0), totalCpuBurst(0), priority(0), remainingCPUBurst(0) {}

int Process::getId() const {
    return id;
}

int Process::getArrivalTime() const {
    return arrivalTime;
}

int Process::getTotalCpuBurst() const {
    return totalCpuBurst;
}

int Process::getPriority() const {
    return priority;
}

int Process::getRemainingCpuBurst() const {
    return remainingCPUBurst;
}

void Process::updatePrioirity(int newPriority) { 
    priority = newPriority; 
}

int Process::getNextPage() {
    return instructionSequence.front().pageNumber;
}

bool Process::executeNextInstruction(){
    if(hasNextInstruction()){
        instructionSequence.pop();
        return true;
    }
    return false;
}

bool Process::insertNextInstruction(int memoryLocation, int pageNumber){
    MemoryLocation newLocation;
    newLocation.memoryLocation = memoryLocation;
    newLocation.pageNumber = pageNumber;
    instructionSequence.push(newLocation);
    return true;
}

void Process::printDEBUG(){
    while(!instructionSequence.empty()){
        cout << "Page Number:" << instructionSequence.front().pageNumber <<
            ", Memory Locatrion:" << instructionSequence.front().memoryLocation << endl;

        instructionSequence.pop();
    }
}

bool Process::hasNextInstruction(){
    return !instructionSequence.empty();
}

int Process::getTotalPages(){
    return instructionSequence.size();
}