#include "../../include/cache/cache.h"
#include <iostream>

using namespace std;

void Cache::init(string level, int size, int line, string policy) {
    this->level = level;
    this->size = size;
    this->lineSize = line;
    this->policy = policy;
    hits = misses = 0;

    cout << "Cache " << level << " initialized "
         << "(size=" << size
         << ", line=" << line
         << ", policy=" << policy << ")\n";
}

void Cache::access(string address) {
    // Dummy simulation: alternate hit/miss
    if ((hits + misses) % 2 == 0) {
        hits++;
        cout << "Cache HIT at " << address << "\n";
    } else {
        misses++;
        cout << "Cache MISS at " << address << "\n";
    }
}

void Cache::stats() {
    cout << "Cache Stats [" << level << "]\n";
    cout << "Hits: " << hits << "\n";
    cout << "Misses: " << misses << "\n";
}
