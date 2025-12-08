// FILE: pager.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Takes input in from user, decides which scheduler to use and sends the output
// Citation: Range Based Iteration https://www.geeksforgeeks.org/cpp/range-based-loop-c/

// EXTRA CREDIT: Implemented the other two paging algorithms but also combined scheduling and paging into one program
// USAGE: ./pager --type <PAGING ALGORITHM> --frames <NUMBER OF FRAMES> --pages <NUMBER OF PAGES> --framesize <FRAME SIZE> --schedFile <SCHEDULER INPUT FILE> --schedType <SCHEDULING ALGORITHM> --preemptive <true/false> --quanta <QUANTA SIZE> <PAGER INPUT FILE (GOES LAST)>
// SCHEDULER DEFAULTS ARE THE SAME AS PREVIOUS PROJECT

#include "pager.h"

using namespace std;

int main(int argc, char **argv) {
    string command, schedResponse, pageResponse;
    int tokens;
    vector<Process> ready;
    queue<Process> schedReady;
    vector<ProcessRunTime> processSequence;

    if (argc > 1){
        commandDecider(argc, argv);
    }

    if (sched & readSchedFile(schedFile, schedType, preemptive, schedReady)){   
        int totalCpuBurst = 0;
        queue<Process> tempQueue = schedReady; // Create a copy of the original queue
        while (!tempQueue.empty()) {
             Process p = tempQueue.front();
             totalCpuBurst += p.getTotalCpuBurst();
             ready.push_back(p); // Also build the ready vector for paging
             tempQueue.pop();
        }
        cout << "Total CPU Burst Time of all processes: " << totalCpuBurst << endl << endl;
        if (schedType == "FCFS") {
            schedResponse += "FCFS: \n";
            FCFS(schedReady, verbose , processSequence, schedResponse);
        } 
        else if (schedType == "SJF" && !preemptive) {
            schedResponse += "SJF (Non-Preemptive): \n";
            SJFNonPreemptive(schedReady, verbose, processSequence ,schedResponse);
        } 
        else if (schedType == "SJF" && preemptive) {
            schedResponse += "SJF (Pre-emptive): \n";
            SJFPreemptive(schedReady, verbose, processSequence, schedResponse);
        }
        else if (schedType == "RR") {
            schedResponse += "Round Robin: \n";
            RoundRobin(schedReady, quanta, verbose, processSequence, schedResponse);
        } 
        else if (schedType == "Priority" && !preemptive) {
            schedResponse += "Priority (Non-Preemptive): \n";
            PriorityNonPreemptive(schedReady, verbose, processSequence, schedResponse);
        } 
        else if (schedType == "Priority" && preemptive) {
            schedResponse += "Priority (Preemptive): \n";
            PriorityPreemptive(schedReady, verbose, processSequence, schedResponse);
        }
        else {
            schedResponse = "Invalid scheduling type selected";
        }
    } 
    else {
        schedResponse = "Error reading file or file is empty";
    }

    for (const auto& entry : processSequence) {
        cout << "Process P_" << entry.processID << " will run for " << entry.runTime << " units." << endl;
    }
    cout << endl;
    
    printf("Pager Type: %s\nFrames: %d\nPages: %d\nFrame Size: %d\nInput File: %s\n", pageType.c_str(), frames, pages, framesize, pageFile.c_str());
    
    if (readPageFile(pageFile, pageType, ready)){
        int pageFaults = 0;
        FrameTable frameTable = FrameTable(frames);

        if (pageType == "FIFO") {
            pageResponse += "FIFO: \n";
            // call FIFO
            if(sched){
                for (int i = 0; i < processSequence.size(); ++i){
                    for (int j = 0; j < ready.size(); ++j){
                        if (processSequence[i].processID == ready[j].getId()){
                            Process &p = ready[j];

                            int totalCPUTime = p.getTotalCpuBurst();
                            int instructionsExecuted = (int) round((double)(processSequence[i].runTime * p.getTotalInstructions()) / totalCPUTime);

                            cout << "Process P_" << p.getId()
                                << " should execute " << instructionsExecuted
                                << " instructions out of " << p.getTotalInstructions() << endl;

                            pageFaults = FIFO(p, frames, frameTable, instructionsExecuted);
                            pageResponse += "Process P_" + to_string(p.getId()) 
                                    + " had " + to_string(pageFaults) + " page faults.\n";  
                            if (!p.hasNextInstruction()){
                                frameTable.free(p.getId());
                            }
                        }
                    }
                }
            }
            else{
                for (int i = 0; i < ready.size(); ++i){
                    Process &p = ready[i];
                    pageFaults = FIFO(p, frames, frameTable, p.getTotalInstructions());
                    pageResponse += "Process P_" + to_string(p.getId()) 
                            + " had " + to_string(pageFaults) + " page faults.\n";
                }
            }
        }
        else if (pageType == "MRU") {
            pageResponse += "MRU: \n";
            // call MRU
            if(sched){
                for (int i = 0; i < processSequence.size(); ++i){
                    for (int j = 0; j < ready.size(); ++j){
                        if (processSequence[i].processID == ready[j].getId() || !sched){
                            Process &p = ready[j];
                            int totalCPUTime = p.getTotalCpuBurst();
                            int instructionsExecuted = (int) round((double)(processSequence[i].runTime * p.getTotalInstructions()) / totalCPUTime);

                            cout << "Process P_" << p.getId()
                                << " should execute " << instructionsExecuted
                                << " instructions out of " << p.getTotalInstructions() << endl;

                            pageFaults = MRU(p, frames, frameTable, instructionsExecuted);
                            pageResponse += "Process P_" + to_string(p.getId()) 
                                    + " had " + to_string(pageFaults) + " page faults.\n";  
                            if (!p.hasNextInstruction()){
                                frameTable.free(p.getId());
                            }
                        }
                    }
                }
            }
            else{
                for (int i = 0; i < ready.size(); ++i){
                    Process &p = ready[i];
                    pageFaults = MRU(p, frames, frameTable, p.getTotalInstructions());
                    pageResponse += "Process P_" + to_string(p.getId()) 
                            + " had " + to_string(pageFaults) + " page faults.\n";  
                }
            }
        }
        else if (pageType == "LRU") {
            pageResponse += "LRU: \n";
            // call LRU
            if(sched){
                for (int i = 0; i < processSequence.size(); ++i){
                    for (int j = 0; j < ready.size(); ++j){
                        if (processSequence[i].processID == ready[j].getId() || !sched){
                            Process &p = ready[j];
                            int totalCPUTime = p.getTotalCpuBurst();
                            int instructionsExecuted = (int) round((double)(processSequence[i].runTime * p.getTotalInstructions()) / totalCPUTime);

                            cout << "Process P_" << p.getId()
                                << " should execute " << instructionsExecuted
                                << " instructions out of " << p.getTotalInstructions() << endl;

                            pageFaults = LRU(p, frames, frameTable, instructionsExecuted);
                            pageResponse += "Process P_" + to_string(p.getId()) 
                                    + " had " + to_string(pageFaults) + " page faults.\n";
                            if (!p.hasNextInstruction()){
                                frameTable.free(p.getId());
                            }  
                        }
                    }
                }
            }
            else{
                for (int i = 0; i < ready.size(); ++i){
                    Process &p = ready[i];
                    pageFaults = LRU(p, frames, frameTable, p.getTotalInstructions());
                    pageResponse += "Process P_" + to_string(p.getId()) 
                            + " had " + to_string(pageFaults) + " page faults.\n";  
                }
            }
        } 
        else if (pageType == "MFU") {
            pageResponse += "MFU: \n";
            // call MFU
            if(sched){
                for (int i = 0; i < processSequence.size(); ++i){
                    for (int j = 0; j < ready.size(); ++j){
                        if (processSequence[i].processID == ready[j].getId() || !sched){
                            Process &p = ready[j];
                            int totalCPUTime = p.getTotalCpuBurst();
                            int instructionsExecuted = (int) round((double)(processSequence[i].runTime * p.getTotalInstructions()) / totalCPUTime);

                            cout << "Process P_" << p.getId()
                                << " should execute " << instructionsExecuted
                                << " instructions out of " << p.getTotalInstructions() << endl;

                            pageFaults = MFU(p, frames, frameTable, instructionsExecuted);
                            pageResponse += "Process P_" + to_string(p.getId()) 
                                    + " had " + to_string(pageFaults) + " page faults.\n";
                            if (!p.hasNextInstruction()){
                                frameTable.free(p.getId());
                            }  
                        }
                    }
                }
            }
            else{
                for (int i = 0; i < ready.size(); ++i){
                    Process &p = ready[i];
                    pageFaults = MFU(p, frames, frameTable, p.getTotalInstructions());
                    pageResponse += "Process P_" + to_string(ready[i].getId()) 
                            + " had " + to_string(pageFaults) + " page faults.\n";
                }
            }
        }
        else if (pageType == "LFU") {
            pageResponse += "LFU: \n";
            // call LFU
            if(sched){
                for (int i = 0; i < processSequence.size(); ++i){
                    for (int j = 0; j < ready.size(); ++j){
                        if (processSequence[i].processID == ready[j].getId() || !sched){
                            Process &p = ready[j];
                            int totalCPUTime = p.getTotalCpuBurst();
                            int instructionsExecuted = (int) round((double)(processSequence[i].runTime * p.getTotalInstructions()) / totalCPUTime);

                            cout << "Process P_" << p.getId()
                                << " should execute " << instructionsExecuted
                                << " instructions out of " << p.getTotalInstructions() << endl;

                            pageFaults = LFU(p, frames, frameTable, instructionsExecuted);
                            pageResponse += "Process P_" + to_string(p.getId()) 
                                    + " had " + to_string(pageFaults) + " page faults.\n";
                            if (!p.hasNextInstruction()){
                                frameTable.free(p.getId());
                            }  
                        }
                    }
                }
            }
            else{
                for (int i = 0; i < ready.size(); ++i){
                    Process &p = ready[i];
                    pageFaults = LFU(p, frames, frameTable, p.getTotalInstructions());
                    pageResponse += "Process P_" + to_string(p.getId()) 
                            + " had " + to_string(pageFaults) + " page faults.\n";
                }
            }
        }
        else if (pageType == "Random") {
            pageResponse += "Random: \n";
            // call Random
            if(sched){
                for (int i = 0; i < processSequence.size(); ++i){
                    for (int j = 0; j < ready.size(); ++j){
                        if (processSequence[i].processID == ready[j].getId() || !sched){
                            Process &p = ready[j];
                            int totalCPUTime = p.getTotalCpuBurst();
                            int instructionsExecuted = (int) round((double)(processSequence[i].runTime * p.getTotalInstructions()) / totalCPUTime);

                            cout << "Process P_" << p.getId()
                                << " should execute " << instructionsExecuted
                                << " instructions out of " << p.getTotalInstructions() << endl;

                            pageFaults = Random(p, frames, frameTable, instructionsExecuted);
                            pageResponse += "Process P_" + to_string(p.getId()) 
                                    + " had " + to_string(pageFaults) + " page faults.\n";
                            if (!p.hasNextInstruction()){
                                frameTable.free(p.getId());
                            }  
                        }
                    }
                }
            }
            else{
                for (int i = 0; i < ready.size(); ++i){
                    Process &p = ready[i];
                    pageFaults = Random(p, frames, frameTable, p.getTotalInstructions());
                    pageResponse += "Process P_" + to_string(p.getId()) 
                            + " had " + to_string(pageFaults) + " page faults.\n";  
                }
            }
        }            
        else {
            pageResponse = "Invalid Paging Algorithm selected";
        }
    } 
    else {
        pageResponse = "Error reading file or file is empty";
    }

    cout << pageResponse << endl;

    return 0;    
}

int commandDecider(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "--type" && i + 1 < argc) {
            pageType = argv[++i];
        } 
        else if (string(argv[i]) == "--frames" && i + 1 < argc) {
            frames = atoi(argv[++i]);
        } 
        else if (string(argv[i]) == "--pages" && i + 1 < argc) {
            pages = atoi(argv[++i]);
        } 
        else if (string(argv[i]) == "--framesize" && i + 1 < argc) {
            framesize = atoi(argv[++i]);
            // Check if framesize is a power of two
            //Citation to check if a number is a power of two: https://stackoverflow.com/questions/108318/how-can-i-test-whether-a-number-is-a-power-of-2
            if ((framesize & (framesize - 1)) != 0 || framesize <= 0) {
                cerr << "Error: Frame size must be a power of two." << endl;
                exit(1);
            }
        }
        else if (string(argv[i]) == "--schedType" && i + 1 < argc) {
            schedType = argv[++i];
        } 
        else if (string(argv[i]) == "--preemptive") {
            preemptive = true;
        } 
        else if (string(argv[i]) == "--quanta" && i + 1 < argc) {
            quanta = atoi(argv[++i]);
        } 
        else if (string(argv[i]) == "--schedFile" && i + 1 < argc) {
            schedFile = argv[++i];
        } 
        else if (string(argv[i]) == "--file" && i + 1 < argc) {
            pageFile = argv[++i];
        } 
        else if (string(argv[i]) == "--sched") {
            sched = true;
        }
        else {
            pageFile = argv[i];
        }
    }
    return 0;
}

bool readPageFile(const string &filename, const string &type, vector <Process > &ready) {
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
        int processIndex = -1;
        Process p(id);
        if (sched){
            for (int i = 0; i < ready.size(); ++i){
                if (ready[i].getId() == id){
                    processIndex = i;
                    break;
                }
            }
        }
        else {
            processIndex = ready.size();
        }

        if (processIndex == -1) {
            cerr << "Process P_" << id << " not found in ready list." << endl;
            return false;
        }

        getline(file, line);
        while (!file.eof() && line[0] != 'P') {
            if(line.empty()){
                getline(file, line);
                continue;
            }
            stringstream ssMem(line);
            int pageNumber;
            ssMem >> memoryLocation;
            if (memoryLocation / framesize >= pages) {
                cerr << "Invalid memory location: " << memoryLocation << " for process P_" << id << endl;
                exit(1);
            }
            if (sched){
                ready[processIndex].insertNextInstruction(memoryLocation, memoryLocation / framesize);
            }
            else{
                p.insertNextInstruction(memoryLocation, memoryLocation / framesize);
            }
            getline(file, line);
        }
        
        // Catches if there is no new line character for the last line of the file
        if(file.eof() && !line.empty() && line[0] != 'P' ) {
            stringstream ssMem(line);
            ssMem >> memoryLocation;
            if (memoryLocation / framesize >= pages) {
                cerr << "Invalid memory location: " << memoryLocation << " for process P_" << id << endl;
                exit(1);
            }   
            if (sched){
                ready[processIndex].insertNextInstruction(memoryLocation, memoryLocation / framesize);
            }
            else{
                p.insertNextInstruction(memoryLocation, memoryLocation / framesize);
            }
        }
        if (sched){
            ready[processIndex].setTotalInstructions();
        }
        else {
            p.setTotalInstructions();
            ready.push_back(p);
        }
    }

    if (empty) {
        cerr << "Input file is empty or improperly formatted." << endl;
    }
    return true;
}
   
bool readSchedFile(const string &filename, const string &type, const bool preemptive, queue<Process> &ready) {
    vector<Process> processes;
    ifstream file(filename);
    string line;

    if (!file) {
        return false;
    }
    
    bool empty = true;
    while (getline(file, line)) {
        empty = false;
        string idStr;
        int id, arrival, burst, priority;
        stringstream ss(line);
        ss >> idStr >> arrival >> burst >> priority;
        id = stoi(idStr.substr(2)); // removes 'P_' prefix so we can compare their integer IDs
        processes.emplace_back(id, arrival, burst, priority);
    }
    if(empty){
        return false;
    }

    sort(processes.begin(), processes.end(), compareByArrival);

    for (Process p : processes) {
        ready.push(p);
    }
    return true;
}

bool compareByArrival(const Process& a, const Process& b) {
    if (a.getArrivalTime() == b.getArrivalTime())
        return a.getId() < b.getId();
    return a.getArrivalTime() < b.getArrivalTime();
}