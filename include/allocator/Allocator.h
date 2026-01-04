#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>

class Allocator {
protected:
    size_t totalMemory;
    size_t usedMemory;

public:
    Allocator(size_t size);
    virtual ~Allocator();

    virtual void allocate(size_t size) = 0;
    virtual void deallocate(int id) = 0;
    virtual void dump() = 0;

    virtual void stats() {
        std::cout << "Total memory: " << totalMemory << std::endl;
        std::cout << "Used memory: " << usedMemory << std::endl;
        std::cout << "Free memory: " << (totalMemory - usedMemory) << std::endl;
    }
};

#endif
