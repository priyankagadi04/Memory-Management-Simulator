#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include "Allocator.h"
#include <vector>
#include "block.h"

class FirstFit : public Allocator {
public:
    int malloc(int size) override;
     
};

#endif

