#ifndef BEST_FIT_H
#define BEST_FIT_H

#include "Allocator.h"
#include <vector>
#include "block.h"

class BestFit : public Allocator {
public:
    int malloc(int size) override;
    
    
};

#endif
