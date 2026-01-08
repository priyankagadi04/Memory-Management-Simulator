#include "../../include/cache/cache.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

Cache::Cache()
    : cacheSize(0),
      lineSize(0),
      associativity(1),
      numSets(0),
      hits(0),
      misses(0),
      accesses(0) {}

void Cache::init(string lvl, int size, int line, int assoc,string pol) {
    level = lvl;
    cacheSize = size;
    lineSize = line;
    policy = pol;
    associativity = assoc; 
    numSets = cacheSize / (lineSize * associativity);

    sets.clear();
    sets.resize(numSets);

    for (int i = 0; i < numSets; i++) {
    sets[i].lines.resize(associativity);
    for (int j = 0; j < associativity; j++) {
        sets[i].lines[j].valid = false;
    }
    }

    hits = misses = accesses = 0;

    cout << "Cache " << level << " initialized "
         << "(size=" << cacheSize
         << ", line=" << lineSize
         <<", assoc=" << associativity
         << ", policy=" << policy << ")" << endl;
}

bool Cache::access(int address) {
    accesses++;

    int block = address / lineSize;
    int setIndex = block % numSets;
    int tag = block / numSets;

    CacheSet &set = sets[setIndex];

    // HIT check
    for (auto &line : set.lines) {
        if (line.valid && line.tag == tag) {
            hits++;
            return true;
        }
    }

    // MISS
    misses++;

    // FIFO replacement
    for (int i = 0; i < associativity; i++) {
        if (!set.lines[i].valid) {
            set.lines[i] = {tag, true};
            set.fifo.push(i);
            return false;
        }
    }

    int evictIndex = set.fifo.front();
    set.fifo.pop();

    set.lines[evictIndex] = {tag, true};
    set.fifo.push(evictIndex);

    return false;
}

void Cache::insert(int address) {
    int block = address / lineSize;
    int setIndex = block % numSets;
    int tag = block / numSets;

    CacheSet &set = sets[setIndex];

    for (int i = 0; i < associativity; i++) {
        if (!set.lines[i].valid) {
            set.lines[i] = {tag, true};
            set.fifo.push(i);
            return;
        }
    }

    int evictIndex = set.fifo.front();
    set.fifo.pop();

    set.lines[evictIndex] = {tag, true};
    set.fifo.push(evictIndex);
}



void Cache::stats() {
    double hitRatio = (accesses == 0) ? 0 : (double)hits / accesses * 100;

    cout << "Cache Stats [" << level << "]" << endl;
    cout<<"Total Accesses: "<<accesses << endl;
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << misses << endl;
    cout << "Hit Ratio: " << hitRatio <<"%"<< endl;
}

