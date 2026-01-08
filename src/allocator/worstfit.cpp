#include "../../include/allocator/Allocator.h"
#include "../../include/allocator/worstfit.h"
#include "../../include/allocator/block.h"

#include <iostream>

int WorstFit::malloc(int size) {
    allocationRequests++;
    Block* curr = head;
    Block* worstBlock = nullptr;
    int worstSize = -1;

    // find worst (largest suitable) block
    while (curr) {
        if (curr->free && curr->size >= size && curr->size > worstSize) {
            worstSize = curr->size;
            worstBlock = curr;
        }
        curr = curr->next;
    }

    if (!worstBlock) {
        allocationFailure++;
        std::cout << "Allocation failed (Worst Fit)\n";
        return -1;
    }

    int oldSize = worstBlock->size;
    if (worstBlock->size > size) {
        Block* newBlock = new Block;
        newBlock->start = worstBlock->start + size;
        newBlock->size = worstBlock->size - size;
        newBlock->free = true;
        newBlock->id = -1;
        newBlock->next = worstBlock->next;

        worstBlock->next = newBlock;
    }

    worstBlock->size = size;
    worstBlock->free = false;
    worstBlock->id = blockCounter++;

    allocationSuccess++;
    totalAllocatedMemory += size;

    std::cout << "Worst Fit allocated block id="
              << worstBlock->id << " size=" << size << std::endl;
    return worstBlock->id;
}
