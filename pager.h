// FILE: pager.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Header file for the main scheduler file
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
#include <algorithm>
#include <queue>
#include "process.h"
#include "Pagers/pagers.h"
#include "Schedulers/schedulers.h"
using namespace std;


// Takes in different commands and sets global variables to it
int commandDecider (int argc, char **argv);

// Reads the input file and builds the initial process queue
bool readSchedFile(const string &filename, const string &type, const bool preemptive, queue<Process> &ready);

// Reads the input file and builds the initial process queue
bool readPageFile(const string &filename, const string &type, vector<Process> &ready);

// Comparator function to sort processes by arrival time
bool compareByArrival(const Process& a, const Process& b);

//initialize Globals

// PAGER GLOBALS
string pageType = "FIFO";
int frames = 3;
int pages = 8;
int framesize = 512;
string pageFile = "pager.in";

// SCHEDULER GLOBALS
string schedType = "FCFS";
bool preemptive = false;
int quanta = 10;
string schedFile = "sched.in";
bool verbose = false;
bool sched = false;
