#ifndef WORST_FIT_H
#define WORST_FIT_H

#include "Allocator.h"
#include <vector>
#include "block.h"

class WorstFit : public Allocator {
public:
    int malloc(int size) override;
    
};

#endif

