#include "../../include/virtual_memory/virtualmemory.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

VirtualMemory::VirtualMemory()
    : numPages(0),
      numFrames(0),
      pageSize(0),
      accesses(0),
      pageFaults(0),
      policy("fifo") {}


void VirtualMemory::init(int pages, int framesCount, int pSize) {
    numPages = pages;
    numFrames = framesCount;
    pageSize = pSize;

    frames.clear();
    pageTable.clear();
    accesses = 0;
    pageFaults = 0;

    cout << "Virtual Memory initialized (pages="
         << numPages << ", frames="
         << numFrames << ", pageSize="
         << pageSize << ")" << endl;
}

void VirtualMemory::setPolicy(string pol) {
    policy = pol;
    cout << "Page Replacement Policy set to "
         << policy << endl;
}
void VirtualMemory::printPageTable() {
    cout << "\nPage Table:\n";
    cout << "Page | Frame\n";
    for (auto &entry : pageTable) {
        cout << "  " << entry.first
             << "   |   " << entry.second << endl;
    }
}


int VirtualMemory::access(int address) {
    accesses++;

    int addr = address;
    int pageNumber = addr / pageSize;
    int offset = addr % pageSize;

    cout << "Virtual Address " << address
         << " → Page " << pageNumber << endl;

    if (pageTable.find(pageNumber) != pageTable.end()) {
        cout << "Page HIT\n";

        int frame = pageTable[pageNumber];
        int physicalAddr = frame * pageSize + offset;

        cout << "Physical Address " << physicalAddr << endl;
        

        
        // LRU update
        if (policy == "lru") {
            frames.erase(remove(frames.begin(), frames.end(), pageNumber),frames.end());
            frames.push_back(pageNumber);
        }
        return physicalAddr;
    }

    // Page fault
    pageFaults++;
    cout << "Page FAULT\n";

    int frame;
    if (frames.size() >= numFrames) {
        int victim = frames.front();
        frames.erase(frames.begin());

        frame=pageTable[victim];
        pageTable.erase(victim);
    }
    else{
        frame=frames.size();
    }

    frames.push_back(pageNumber);
    pageTable[pageNumber] = frame;

    int physicalAddr = frame * pageSize + offset;
    cout << "Physical Address " << physicalAddr << endl;
    return physicalAddr;
}

void VirtualMemory::stats() {
    cout << "Virtual Memory Stats" << endl;
    cout << "Accesses: " << accesses << endl;
    cout << "Page Faults: " << pageFaults << endl;
}

