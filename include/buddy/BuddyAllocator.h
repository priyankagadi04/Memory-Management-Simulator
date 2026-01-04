#ifndef BUDDY_ALLOCATOR_H
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

#endif


