#include <iostream>
#include <iomanip>
#include "../../include/allocator/Allocator.h"
#include "../../include/allocator/block.h"

using namespace std;

Allocator::Allocator() {
    head = nullptr;
    totalMemory = 0;
    blockCounter = 1;

    allocationRequests = 0;
    allocationSuccess = 0;
    allocationFailure = 0;
    totalAllocatedMemory = 0;
    internalFragmentation = 0;
}

Allocator::~Allocator() {
    Block* curr = head;
    while (curr) {
        Block* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

void Allocator::initMemory(int size) {
    Block* curr = head;
    while (curr) {
        Block* temp = curr;
        curr = curr->next;
        delete temp;
    }
    totalMemory = size;
    blockCounter = 1;
    head = new Block;
    head->start = 0;
    head->size = size;
    head->free = true;
    head->id = -1;
    head->next = nullptr;


    allocationRequests = 0;
    allocationSuccess = 0;
    allocationFailure = 0;
    totalAllocatedMemory = 0;
    internalFragmentation = 0;

    cout << "Memory initialized with size " << size <<"bytes"<< endl;
}

void Allocator::freeBlock(int id) {
    Block* curr = head;
    Block* prev = nullptr;
    while (curr) {
        if (!curr->free && curr->id == id) {
            curr->free = true;
            curr->id = -1;
            totalAllocatedMemory -= curr->size;

            bool merged=false;
            // Coalesce with next
            if (curr->next && curr->next->free) {
                Block* temp = curr->next;
                curr->size += temp->size;
                curr->next = temp->next;
                delete temp;
                merged=true;
            }


            if (prev && prev->free) {
                prev->size += curr->size;
                prev->next = curr->next;
                delete curr;
                curr=prev;
                merged=true;
            }
            if (totalAllocatedMemory == 0) {
                internalFragmentation = 0;
            }

            if (merged)
                cout << "Block " << id << " freed and merged\n";
            else
                cout << "Block " << id << " freed\n";
            return;
        }
        prev=curr;
        curr = curr->next;
    }

    cout << "Invalid block ID\n";
}

void Allocator::dumpMemory() {
    Block* curr = head;
    cout << "\nMemory Dump:\n";

    while (curr) {
        cout << "["
             << setw(4) << curr->start
             << " - "
             << setw(4) << curr->start + curr->size - 1
             << "] ";

        if (curr->free)
            cout << "FREE\n";
        else
            cout << "USED (id=" << curr->id << ")\n";

        curr = curr->next;
    }
}

double Allocator::calculateExternalFragmentation() {
    int totalFree = 0;
    int largestFree = 0;

    Block* curr = head;
    while (curr) {
        if (curr->free) {
            totalFree += curr->size;
            if (curr->size > largestFree)
                largestFree = curr->size;
        }
        curr = curr->next;
    }

    if (totalFree == 0) return 0.0;

    return (1.0 - (double)largestFree / totalFree);
}

double Allocator::calculateMemoryUtilization() {
    if (totalMemory == 0) return 0.0;
    return (double)totalAllocatedMemory / totalMemory;
}

double Allocator::getSuccessRate() {
    if (allocationRequests == 0) return 0.0;
    return (double)allocationSuccess / allocationRequests;
}

double Allocator::getFailureRate() {
    if (allocationRequests == 0) return 0.0;
    return (double)allocationFailure / allocationRequests;
}

void Allocator::printStats() {
    cout << "\n===== Memory Statistics =====\n";
    cout << "Total Memory           : " << totalMemory << endl;
    cout << "Used Memory            : " << totalAllocatedMemory << endl;

    cout << "Memory Utilization     : "
         << calculateMemoryUtilization() * 100 << "%\n";

    cout << "Internal Fragmentation : "
         << internalFragmentation << " bytes\n";

    cout << "External Fragmentation : "
         << calculateExternalFragmentation() * 100 << "%\n";

    cout << "Allocation Requests    : " << allocationRequests << endl;
    cout << "Allocation Success     : " << allocationSuccess << endl;
    cout << "Allocation Failure     : " << allocationFailure << endl;

    cout << "Success Rate           : "
         << getSuccessRate() * 100 << "%\n";

    cout << "Failure Rate           : "
         << getFailureRate() * 100 << "%\n";
}