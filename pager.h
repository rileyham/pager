// FILE: pager.h
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
// Header file for the main scheduler file
//

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include "process.h"
using namespace std;


// Takes in different commands and sets global variables to it
int commandDecider (int argc, char **argv);

// readfile
// Reads the input file and builds the initial process queue
bool readFile(const string &filename, const string &type, map<Process, queue<int> > &ready);

// compareByArrival
// Comparator function to sort processes by arrival time

//initialize Globals
string type = "FIFO";
int frames = 3;
int pages = 8;
int framesize = 512;
string file = "pager.in";
