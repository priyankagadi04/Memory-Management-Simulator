#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <string>

class VirtualMemory {
private:
    int pages, frames, pageSize;
    int pageFaults, accesses;
    std::string policy;
public:
    void init(int pages, int frames, int pageSize);
    void setPolicy(std::string policy);
    void access(std::string address);
    void stats();
};

#endif
