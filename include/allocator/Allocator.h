#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include "block.h"
#include <iostream>
using namespace std;

class Allocator {
protected:
    Block* head;
    int nextId;
    int totalMemory;
    int blockCounter;


    // ---- Statistics ----
    int allocationRequests;
    int allocationSuccess;
    int allocationFailure;

    int totalAllocatedMemory;
    int internalFragmentation;

public:
    Allocator();
    virtual ~Allocator();

    void initMemory(int size);

    // Allocation algorithms will use this
    virtual int malloc(int size) = 0;

    void freeBlock(int id);
    void dumpMemory();
    void printStats();

    // Metric helpers
    double calculateExternalFragmentation();
    double calculateMemoryUtilization();
    double getSuccessRate();
    double getFailureRate();
};

#endif

