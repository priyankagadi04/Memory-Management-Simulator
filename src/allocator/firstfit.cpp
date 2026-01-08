#include "../../include/allocator/Allocator.h"
#include "../../include/allocator/firstfit.h"
#include "../../include/allocator/block.h"

#include <iostream>
#include <limits>

int FirstFit::malloc(int size) {
    allocationRequests++;

    Block* curr = head;

    while (curr) {
        if (curr->free && curr->size >= size) {

            int oldSize = curr->size;

            // split block if needed
            if (curr->size > size) {
                Block* newBlock = new Block;
                newBlock->start = curr->start + size;
                newBlock->size = curr->size - size;
                newBlock->free = true;
                newBlock->id = -1;
                newBlock->next = curr->next;

                curr->next = newBlock;
            }

            curr->size = size;
            curr->free = false;
            curr->id = blockCounter++;
            allocationSuccess++;
            totalAllocatedMemory += size;
            

            std::cout << "First Fit allocated block id="
                      << curr->id << " size=" << size << std::endl;

            return curr->id;
        }
        curr = curr->next;
    }

    allocationFailure++;
    std::cout << "Allocation failed: insufficient memory" << std::endl;
    return -1;
}

