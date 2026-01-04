#include "../../include/allocator/bestfit.h"
#include <iostream>

#include "../../include/allocator/block.h"


bestfit::bestfit(size_t size) : Allocator(size) {
    counter = 0;
}

void bestfit::allocate(size_t size) {
    if (usedMemory + size > totalMemory) {
        std::cout << "Allocation failed: no suitable block\n";
        return;
    }

    blocks.push_back({counter++, size});
    usedMemory += size;

    std::cout << "Best Fit allocated block " << counter - 1
              << " of size " << size << std::endl;
}

void bestfit::deallocate(int id) {
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

void bestfit::dump() {
    std::cout << "Memory Dump (Best Fit):\n";
    for (auto &b : blocks)
        std::cout << "Block " << b.id << ": size = " << b.size << std::endl;
}
