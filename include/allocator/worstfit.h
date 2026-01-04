#ifndef WORST_FIT_H
#define WORST_FIT_H

#include "Allocator.h"
#include <vector>
#include "block.h"

class WorstFit : public Allocator {
    int counter;
    std::vector<Block> blocks;

public:
    WorstFit(size_t size);
    void allocate(size_t size) override;
    void deallocate(int id) override;
    void dump() override;
};

#endif

