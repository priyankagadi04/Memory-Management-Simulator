/*#ifndef BUDDY_ALLOCATOR_H
#define BUDDY_ALLOCATOR_H

#include <vector>
#include <iostream>

struct BuddyBlock {
    int id;
    size_t size;
};

class BuddyAllocator {
    size_t totalSize;
    size_t usedSize;
    int counter;
    std::vector<BuddyBlock> blocks;

public:
    BuddyAllocator(size_t size);

    void allocate(size_t size);
    void deallocate(int id);
    void dump();
    void stats();
};

#endif*/
#ifndef BUDDY_ALLOCATOR_H
#define BUDDY_ALLOCATOR_H
#include <map>
#include <unordered_map>
#include <vector>
#include <cstddef>

struct BuddyBlock {
    size_t allocatedSize;   // power-of-two size
    size_t requestedSize;
};

class BuddyAllocator {
private:
    size_t total;
    int nextId;

    std::map<int, BuddyBlock> used;
    size_t nextPowerOfTwo(size_t n);

public:
    BuddyAllocator();

    void initMemory(size_t size);
    int allocate(size_t size);
    void freeBlock(int id);

    void dumpMemory();
    void stats();
};

#endif



