#include "../../include/allocator/Allocator.h"

// Constructor
Allocator::Allocator(size_t size) {
    totalMemory = size;
    usedMemory = 0;
}

// Virtual Destructor (IMPORTANT for polymorphism)
Allocator::~Allocator() {
    // nothing to clean here
}

/*#include <iostream>
#include <iomanip>
#include "../../include/allocator/Allocator.h"

using namespace std;

Allocator::Allocator(size_t size) {
    totalMemory = size;
    blockCounter = 1;
}

Allocator::~Allocator() {}

void Allocator::initMemory(int size) {
    totalMemory = size;
    blockCounter = 1;

    head = new Block{0, size, true, -1, nullptr};

    cout << "Memory initialized: " << size << " bytes\n";
}

void Allocator::freeBlock(int id) {
    Block* curr = head;

    while (curr) {
        if (!curr->free && curr->id == id) {
            curr->free = true;
            curr->id = -1;
            cout << "Block " << id << " freed\n";
            break;
        }
        curr = curr->next;
    }

    // coalescing
    curr = head;
    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

void Allocator::dumpMemory() {
    Block* curr = head;
    while (curr) {
        cout << "[0x" << hex << curr->start << " - 0x"
             << curr->start + curr->size - 1 << dec << "] ";

        if (curr->free)
            cout << "FREE\n";
        else
            cout << "USED (id=" << curr->id << ")\n";

        curr = curr->next;
    }
}

void Allocator::printStats() {
    int used = 0, freeMem = 0, largestFree = 0;

    Block* curr = head;
    while (curr) {
        if (curr->free) {
            freeMem += curr->size;
            largestFree = max(largestFree, curr->size);
        } else {
            used += curr->size;
        }
        curr = curr->next;
    }

    cout << "Total memory: " << totalMemory << "\n";
    cout << "Used memory: " << used << "\n";
    cout << "Free memory: " << freeMem << "\n";

    if (freeMem > 0) {
        double extFrag =
            (double)(freeMem - largestFree) / totalMemory * 100;
        cout << "External Fragmentation: " << extFrag << "%\n";
    }
}*/
