#include "../../include/virtual_memory/virtualmemory.h"
#include <iostream>

using namespace std;

void VirtualMemory::init(int pages, int frames, int pageSize) {
    this->pages = pages;
    this->frames = frames;
    this->pageSize = pageSize;
    pageFaults = accesses = 0;

    cout << "Virtual Memory initialized "
         << "(pages=" << pages
         << ", frames=" << frames
         << ", pageSize=" << pageSize << ")\n";
}

void VirtualMemory::setPolicy(string policy) {
    this->policy = policy;
    cout << "Page Replacement Policy set to " << policy << "\n";
}

void VirtualMemory::access(string address) {
    accesses++;

    // Dummy logic: every 2nd access causes a fault
    if (accesses % 2 == 0) {
        pageFaults++;
        cout << "Page FAULT at " << address << "\n";
    } else {
        cout << "Page HIT at " << address << "\n";
    }
}

void VirtualMemory::stats() {
    cout << "Virtual Memory Stats\n";
    cout << "Accesses: " << accesses << "\n";
    cout << "Page Faults: " << pageFaults << "\n";
}
