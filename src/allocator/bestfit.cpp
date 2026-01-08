#include "../../include/allocator/allocator.h"
#include "../../include/allocator/bestfit.h"
#include "../../include/allocator/block.h"
#include <iostream>
#include <climits>

int BestFit::malloc(int size) {
    allocationRequests++;
    Block* curr = head;
    Block* bestBlock = nullptr;
    int bestSize = INT_MAX;

    // find best (smallest suitable) block
    while (curr) {
        if (curr->free && curr->size >= size && curr->size < bestSize) {
            bestSize = curr->size;
            bestBlock = curr;
        }
        curr = curr->next;
    }

    if (!bestBlock) {
        allocationFailure++;
        std::cout << "Allocation failed (Best Fit)\n";
        return -1;
    }

    int oldSize = bestBlock->size;

    // split block if needed
    if (bestBlock->size > size) {
        Block* newBlock = new Block;
        newBlock->start = bestBlock->start + size;
        newBlock->size = bestBlock->size - size;
        newBlock->free = true;
        newBlock->id = -1;
        newBlock->next = bestBlock->next;

        bestBlock->next = newBlock;
    }

    bestBlock->size = size;
    bestBlock->free = false;
    bestBlock->id = blockCounter++;

    allocationSuccess++;                 
    totalAllocatedMemory += size;         
    std::cout << "Best Fit allocated block id="
              << bestBlock->id << " size=" << size << std::endl;

    return bestBlock->id;
    
}

