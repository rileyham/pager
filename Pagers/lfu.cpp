// FILE: lfu.cpp
// Group 1: Chase Gartner, Ryan Geisler, Riley Ham
// Operating Systems, Fall 2025
//
#include "lfu.h"
#include <vector>
using namespace std;

int LFU(Process p, int frames) {
   int pageFaults = 0;


   if (frames <= 0) {
       return 0;
   }
   // frame table
   // -1 means the frame is empty
   vector<int> frameTable(frames, -1);
  
    // frequency table: how many times each frame's page has been used
   vector<int> freq(frames, 0);

   //how many frames are being used
   int filled = 0;

   while (p.hasNextInstruction()) {
       int page = p.getNextPage();
       bool hit = false;


       // check if the page is already in the frame table
       for (int i = 0; i < frames; i++) {
           if (frameTable[i] == page) {
               // page hit, increase the freq
               freq[i] = freq[i] + 1;
               hit = true;
               break;
           }
       }

       if (!hit) {
           pageFaults++;

           if (filled < frames) {
               // still an empty frame so put the page here
               frameTable[filled] = page;
               freq[filled] = 1;   // first time we see this page
               filled = filled + 1;
           } else {
               // all frames are full
               // find the frame with the smallest frequency
               int lfuIndex = 0;
               for (int i = 1; i < frames; i++) {
                   if (freq[i] < freq[lfuIndex]) {
                       lfuIndex = i;
                   }
               }

               // replace the lfu page
               frameTable[lfuIndex] = page;
               freq[lfuIndex] = 1;
           }
       }


       p.executeNextInstruction();
   }


   return pageFaults;
}
