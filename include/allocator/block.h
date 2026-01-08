#ifndef BLOCK_H
#define BLOCK_H
#include <cstdlib>
struct Block {
        int id;
        int start;
        int  size;
        size_t requested;
        bool free;
        Block* next;
};

#endif
