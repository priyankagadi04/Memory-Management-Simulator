#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include "Allocator.h"
#include <vector>
#include "block.h"

class firstfit : public Allocator {
    int counter;
    std::vector<Block> blocks;
public:
    firstfit(size_t size);
    void allocate(size_t size) override;
    void deallocate(int id) override;
    void dump() override;  
};

#endif

