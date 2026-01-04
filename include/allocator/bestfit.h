#ifndef BEST_FIT_H
#define BEST_FIT_H

#include "Allocator.h"
#include <vector>
#include "block.h"

class bestfit : public Allocator {
    int counter;
    std::vector<Block> blocks;
public:
    bestfit(size_t size);
    void allocate(size_t size) override;
    void deallocate(int id) override;
    void dump() override;
    
};

#endif
