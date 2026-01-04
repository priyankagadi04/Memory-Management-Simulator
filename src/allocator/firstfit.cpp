#include "../../include/allocator/firstfit.h"
#include <iostream>
#include "../../include/allocator/block.h"


firstfit::firstfit(size_t size) : Allocator(size) {
    counter = 0;
}

void firstfit::allocate(size_t size) {
    if (usedMemory + size > totalMemory) {
        std::cout << "Allocation failed: insufficient memory\n";
        return;
    }

    blocks.push_back({counter++, size});
    usedMemory += size;

    std::cout << "Allocated block " << counter - 1
              << " of size " << size << std::endl;
}

void firstfit::deallocate(int id) {
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->id == id) {
            usedMemory -= it->size;
            std::cout << "Freed block " << id << std::endl;
            blocks.erase(it);
            return;
        }
    }
    std::cout << "Invalid block id\n";
}

void firstfit::dump() {
    std::cout << "Memory Dump (First Fit):\n";
    for (auto &b : blocks)
        std::cout << "Block " << b.id << ": size = " << b.size << std::endl;
}

