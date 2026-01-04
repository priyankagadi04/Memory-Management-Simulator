#ifndef CACHE_H
#define CACHE_H

#include <string>

class Cache {
private:
    std::string level, policy;
    int size, lineSize;
    int hits, misses;
public:
    void init(std::string level, int size, int line, std::string policy);
    void access(std::string address);
    void stats();
};

#endif