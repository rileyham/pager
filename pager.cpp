// FILE: scheduler.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Takes input in from user, decides which scheduler to use and sends the output
// Citation: Range Based Iteration https://www.geeksforgeeks.org/cpp/range-based-loop-c/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "process.h"
#include <map>
#include <queue>
#include "pager.h"
using namespace std;

int main(int argc, char **argv) {
    string command, response;
    int tokens;
    map<Process, queue<int> > ready;

    if (argc > 1){
        commandDecider(argc, argv);
    }

    printf("Pager Type: %s\nFrames: %d\nPages: %d\nFrame Size: %d\nInput File: %s\n", type.c_str(), frames, pages, framesize, file.c_str());
    
    if (readFile(file, type, ready)){
        if (type == "FIFO") {
            response += "FIFO: \n";
            // call FIFO
        } 
        else if (type == "LRU") {
            response += "LRU: \n";
            // call LRU
        } 
        else if (type == "MFU") {
            response += "MFU: \n";
            // call MFU
        }
        else if (type == "Random") {
            response += "Random: \n";
            // call Random
        }            
        else {
            response = "Invalid scheduling type selected";
        }
    } 
    else {
        response = "Error reading file or file is empty";
    }

    cout << response << endl;
    return 0;    
}

int commandDecider(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "--type" && i + 1 < argc) {
            type = argv[++i];
        } 
        else if (string(argv[i]) == "--frames" && i + 1 < argc) {
            frames = atoi(argv[++i]);
        } 
        else if (string(argv[i]) == "--pages" && i + 1 < argc) {
            pages = atoi(argv[++i]);
        } 
        else if (string(argv[i]) == "--framesize" && i + 1 < argc) {
            framesize = atoi(argv[++i]);
        }
        else if (string(argv[i]) == "--file" && i + 1 < argc) {
            file = argv[++i];
        }  
        else {
            cerr << "Invalid or incomplete option: " << argv[i] << endl;
        }
    }
    return 0;
}

bool readFile(const string &filename, const string &type, map<Process, queue<int> > &ready) {
    ifstream file(filename);
    string line;
    queue<int> memoryLocations;

    if (!file) {
        return false;
    }

    bool empty = true;
    getline(file, line);
    while (!file.eof()) {
        empty = false;
        string idStr;
        int id, memoryLocation;
        stringstream ss(line);
        ss >> idStr;

        if (idStr.empty() || idStr.substr(0, 2) != "P_") {
            cerr << "Invalid process ID format: " << idStr << endl;
            return false;
        }

        id = stoi(idStr.substr(2)); 
        Process p(id);
        queue<int> memoryLocations;

        getline(file, line);
        while (!file.eof() && line[0] != 'P') {
            stringstream ssMem(line);
            ssMem >> memoryLocation;
            printf("Read memory location %d for process %s\n", memoryLocation, idStr.c_str());
            memoryLocations.push(memoryLocation);
            getline(file, line);
        }

        ready[p] = memoryLocations;
    }
    if (empty) {
        cerr << "Input file is empty or improperly formatted." << endl;
    }
    return true;
}