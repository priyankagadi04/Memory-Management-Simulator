#include "../../include/buddy/BuddyAllocator.h"
#include <iostream>

using namespace std;

BuddyAllocator::BuddyAllocator()
    : total(0), nextId(0) {}

void BuddyAllocator::initMemory(size_t size) {
    total = size;
    used.clear();
    nextId = 0;

    cout << "Buddy system initialized with size "
         << size << endl;
}
size_t BuddyAllocator::nextPowerOfTwo(size_t n) {
    size_t power = 1;
    while (power < n)
        power <<= 1;
    return power;
}
int BuddyAllocator::allocate(size_t size) {
    size_t allocSize = nextPowerOfTwo(size);

    size_t usedMem = 0;
    for (auto &p : used)
        usedMem += p.second.allocatedSize;

    if (usedMem + allocSize > total) {
        cout << "Buddy allocation failed\n";
        return -1;
    }
    int id=nextId++;
    used[id] = {allocSize, size};
    cout << "Buddy allocated block "
         << id
         << " of size "
         << allocSize << endl;

    return id;
}

void BuddyAllocator::freeBlock(int id) {
    auto it = used.find(id);
    if (it == used.end()) {
        std::cout << "Invalid Buddy bloc id" << std::endl;
        return;
    }

    std::cout << "Buddy freed block " << id << std::endl;
    used.erase(it);
}

void BuddyAllocator::dumpMemory() {
    for (auto &p : used)
        std::cout << "Block " << p.first
                  << ": allocatedSize = " << p.second.allocatedSize
                  << ": requestedSize = " << p.second.requestedSize
                  <<  std::endl;
}

void BuddyAllocator::stats() {
    size_t usedMem = 0;
    size_t internalFrag = 0;
    for (auto &p : used){
        usedMem += p.second.allocatedSize;
        internalFrag+=(p.second.allocatedSize - p.second.requestedSize);
    }

    std::cout << "Total Size: " << total << std::endl;
    std::cout << "Used: " << usedMem << std::endl;
    std::cout << "Free: " << total - usedMem << std::endl;
    std::cout << "Internal Fragmentation: " << internalFrag << std::endl;

}

