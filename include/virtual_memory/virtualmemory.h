#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class VirtualMemory {
private:
    int numPages;
    int numFrames;
    int pageSize;

    string policy;

    vector<int> frames;
    unordered_map<int, int> pageTable;

    int accesses;
    int pageFaults;


public:
    VirtualMemory();

    void init(int pages, int frames, int pageSize);
    void setPolicy(string pol);
    void printPageTable();
    int access(int address);
    void stats();
};

#endif

