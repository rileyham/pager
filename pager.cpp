// FILE: pager.cpp
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
    vector<Process> ready;

    if (argc > 1){
        commandDecider(argc, argv);
    }

    printf("Pager Type: %s\nFrames: %d\nPages: %d\nFrame Size: %d\nInput File: %s\n", type.c_str(), frames, pages, framesize, file.c_str());
    
    if (readFile(file, type, ready)){
        int pageFaults = 0;
        if (type == "FIFO") {
            response += "FIFO: \n";
            // call FIFO
            for (int i = 0; i < ready.size(); ++i){
                pageFaults = FIFO(ready[i], frames);
                response += "Process P_" + to_string(ready[i].getId()) + " had " + to_string(pageFaults) + " page faults.\n";  
            }
        }
        else if (type == "MRU") {
            response += "MRU: \n";
            // call MRU
            for (int i = 0; i < ready.size(); ++i){
                //pageFaults = MRU(ready[i], frames);
                //response += "Process P_" + to_string(ready[i].getId()) + " had " + to_string(pageFaults) + " page faults.\n";  
            }
        }
        else if (type == "LRU") {
            response += "LRU: \n";
            // call LRU
            for (int i = 0; i < ready.size(); ++i){
                pageFaults = LRU(ready[i], frames);
                response += "Process P_" + to_string(ready[i].getId()) + " had " + to_string(pageFaults) + " page faults.\n";  
            }
        } 
        else if (type == "MFU") {
            response += "MFU: \n";
            // call MFU
            for (int i = 0; i < ready.size(); ++i){
                pageFaults = MFU(ready[i], frames, pages);
                response += "Process P_" + to_string(ready[i].getId()) + " had " + to_string(pageFaults) + " page faults.\n";  
            }
        }
        else if (type == "LFU") {
            response += "LFU: \n";
            // call LFU
            for (int i = 0; i < ready.size(); ++i){
                //pageFaults = LFU(ready[i], frames);
                //response += "Process P_" + to_string(ready[i].getId()) + " had " + to_string(pageFaults) + " page faults.\n";  
            }
        }
        else if (type == "Random") {
            response += "Random: \n";
            // call Random
            for (int i = 0; i < ready.size(); ++i){
                pageFaults = Random(ready[i], frames);
                response += "Process P_" + to_string(ready[i].getId()) + " had " + to_string(pageFaults) + " page faults.\n";  
            }
        }            
        else {
            response = "Invalid Paging Algorithm selected";
        }
    } 
    else {
        response = "Error reading file or file is empty";
    }

    cout << response << endl;
    for (int i = 0; i < ready.size(); ++i){
        //cout << "Process P_" << ready[i].getId() << " sequence of instructions" << endl;
        //ready[i].printDEBUG();
        //cout << endl;
    }
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

bool readFile(const string &filename, const string &type, vector <Process > &ready) {
    ifstream file(filename);
    string line;

    if (!file) {
        return false;
    }

    bool empty = true;
    getline(file, line);
    while (!file.eof()) {
        if(line.empty()){
            getline(file, line);
            continue;
        }
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

        getline(file, line);
        while (!file.eof() && line[0] != 'P') {
            if(line.empty()){
                getline(file, line);
                continue;
            }
            stringstream ssMem(line);
            int pageNumber;
            ssMem >> memoryLocation;
            //printf("Read memory location %d for process %s\n", memoryLocation, idStr.c_str());
            p.insertNextInstruction(memoryLocation, memoryLocation / framesize);
            getline(file, line);
        }
        
        // Catches if there is no new line character for the last line of the file
        if(file.eof() && !line.empty() && line[0] != 'P' ) {
            stringstream ssMem(line);
            ssMem >> memoryLocation;   
            //printf("Read memory location %d for process %s\n", memoryLocation, idStr.c_str());
            p.insertNextInstruction(memoryLocation, memoryLocation / framesize);
        }

        ready.push_back(p);
    }
    if (empty) {
        cerr << "Input file is empty or improperly formatted." << endl;
    }
    return true;
}

    

