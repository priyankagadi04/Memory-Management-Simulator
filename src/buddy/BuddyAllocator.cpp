#include "../../include/buddy/BuddyAllocator.h"

BuddyAllocator::BuddyAllocator(size_t size) {
    totalSize = size;
    usedSize = 0;
    counter = 0;
}

void BuddyAllocator::allocate(size_t size) {
    if (usedSize + size > totalSize) {
        std::cout << "Buddy allocation failed\n";
        return;
    }

    blocks.push_back({counter++, size});
    usedSize += size;
    std::cout << "Buddy allocated block " << counter - 1
              << " of size " << size << std::endl;
}

void BuddyAllocator::deallocate(int id) {
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->id == id) {
            usedSize -= it->size;
            blocks.erase(it);
            std::cout << "Buddy freed block " << id << std::endl;
            return;
        }
    }
    std::cout << "Invalid Buddy block id\n";
}

void BuddyAllocator::dump() {
    std::cout << "Buddy Memory Dump:\n";
    for (auto &b : blocks)
        std::cout << "Block " << b.id << ": size = " << b.size << std::endl;
}

void BuddyAllocator::stats() {
    std::cout << "Buddy Stats:\n";
    std::cout << "Total Size: " << totalSize << std::endl;
    std::cout << "Used: " << usedSize << std::endl;
    std::cout << "Free: " << (totalSize - usedSize) << std::endl;
}

