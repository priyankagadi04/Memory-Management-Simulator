#include "../../include/allocator/worstfit.h"
#include <iostream>
#include "../../include/allocator/block.h"


WorstFit::WorstFit(size_t size) : Allocator(size) {
    counter = 0;
}

void WorstFit::allocate(size_t size) {
    if (usedMemory + size > totalMemory) {
        std::cout << "Allocation failed: insufficient memory\n";
        return;
    }

    blocks.push_back({counter++, size});
    usedMemory += size;

    std::cout << "Worst Fit allocated block " << counter - 1
              << " of size " << size << std::endl;
}

void WorstFit::deallocate(int id) {
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

void WorstFit::dump() {
    std::cout << "Memory Dump (Worst Fit):\n";
    for (auto &b : blocks)
        std::cout << "Block " << b.id << ": size = " << b.size << std::endl;
}

