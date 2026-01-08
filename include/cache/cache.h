#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>

using namespace std;
struct CacheLine {
    int tag;
    bool valid;
};

struct CacheSet {
    vector<CacheLine> lines;   // N-way lines
    queue<int> fifo;           // FIFO replacement
};

class Cache {
private:
    string level;
    int cacheSize;
    int lineSize;
    string policy;

    unordered_set<std::string> lines;

    int associativity;          // 1 = direct-mapped, >1 = set-associative
    int numSets;
    vector<CacheSet> sets;


    int hits;
    int misses;
    int accesses;

public:
    Cache();

    void init(string lvl, int size, int line,int assoc,string pol);
    bool access(int address);
    void insert(int address);
    void stats();
};

#endif
