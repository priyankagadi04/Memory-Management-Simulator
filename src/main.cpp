#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "../include/allocator/allocator.h"
#include "../include/buddy/BuddyAllocator.h"
#include "../include/cache/cache.h"
#include "../include/virtual_memory/virtualmemory.h"

#include "../include/allocator/firstfit.h"
#include "../include/allocator/bestfit.h"
#include "../include/allocator/worstfit.h"

using namespace std;
enum AllocatorMode {
    NORMAL,
    BUDDY
};
void accessMemory(int address, Cache &L1, Cache &L2) {
    cout << "Accessing cache with Physical Address " << address << endl;
    if (L1.access(address)) cout<<"L1 Hit\n";
    else{
        cout<<"L1 Miss\n";
        if (L2.access(address)) {
            cout<<"L2 Hit\n";
        }
        else{
            cout<<"L2 Miss\n";
            L2.insert(address);
        }
    }
    L1.insert(address);
}

int main() {
    Allocator* allocator = nullptr;
    BuddyAllocator buddy;
    Cache cache;
    VirtualMemory vm;

    AllocatorMode mode = NORMAL;
    size_t globalmemorysize = 0;
    string line;

    Cache cacheL1;
    Cache cacheL2;


    cout << "Memory Management Simulator" << endl;

    while (getline(cin, line)) {
        // Ignore empty lines and comments
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);
        vector<string> tokens;
        string word;

        while (ss >> word)
            tokens.push_back(word);

        // ---------- init memory ----------
        if (tokens[0] == "init" && tokens[1] == "memory") {
            globalmemorysize = stoul(tokens[2]);
            buddy.initMemory(globalmemorysize);
            if (allocator)allocator->initMemory(globalmemorysize);
            std::cout << "Physical memory initialized: "
              << globalmemorysize << std::endl;
        }

        // ---------- set allocator ----------
        else if (tokens[0] == "set" && tokens[1] == "allocator") {
            if (allocator){
                delete allocator;
                allocator=nullptr;
            }
            if (tokens[2] == "first_fit") {
                allocator = new FirstFit();
                allocator->initMemory(globalmemorysize);
                mode = NORMAL;
                cout << "Allocator set to First Fit" << endl;
            }
            else if (tokens[2] == "best_fit") {
                allocator = new BestFit();
                allocator->initMemory(globalmemorysize);
                mode = NORMAL;
                cout << "Allocator set to Best Fit" << endl;
            }
            else if (tokens[2] == "worst_fit") {
                allocator = new WorstFit();
                allocator->initMemory(globalmemorysize);
                mode = NORMAL;
                cout << "Allocator set to Worst Fit" << endl;
            }
            else if (tokens[2] == "buddy") {
                mode=BUDDY;
                if (allocator) {
                    delete allocator;
                    allocator = nullptr;
                }
                cout << "Allocator set to Buddy System" << endl;
            }

        } 

        // ---------- malloc ----------
        else if (tokens[0] == "malloc") {
            size_t size = stoul(tokens[1]);

            if (mode==NORMAL && allocator)
                allocator->malloc(size);
            else if(mode==BUDDY){
                buddy.allocate(size);
            }
        }

        // ---------- free ----------
        else if (tokens[0] == "free") {
            int index = stoi(tokens[1]);

            if (mode==NORMAL && allocator)
                allocator->freeBlock(index);
            else if(mode==BUDDY)
                buddy.freeBlock(index);
        }

        // ---------- dump memory ----------
        else if (tokens[0] == "dump" && tokens[1] == "memory") {
            if (mode==NORMAL && allocator)
                allocator->dumpMemory();
            else if(mode==BUDDY)
                buddy.dumpMemory();
        }

        // ---------- stats ----------
        else if (tokens[0] == "stats") {
            if (mode==NORMAL && allocator)
                allocator->printStats();
            else if(mode==BUDDY)
                buddy.stats();
        }

        // ---------- cache ----------
        else if (tokens[0] == "cache") {
            if (tokens[1] == "init") {
                string level = tokens[2];
                int size = stoi(tokens[3]);
                int lineSize = stoi(tokens[4]);
                int assoc = stoi(tokens[5]);
                string policy = tokens[6];

                if (level == "L1") cacheL1.init(level, size, lineSize,assoc, policy);
                else if (level == "L2") cacheL2.init(level, size, lineSize, assoc,policy);
            }
            else if (tokens[1] == "access") {
                int addr=stoi(tokens[2]);
                accessMemory(addr,cacheL1,cacheL2);
            }
            else if (tokens[1] == "stats") {
                cacheL1.stats();
                cacheL2.stats();
            }
        }

        // ---------- virtual memory ----------
        else if (tokens[0] == "vm") {
            if (tokens[1] == "init") {
                int pages = stoi(tokens[2]);
                int frames = stoi(tokens[3]);
                int pageSize = stoi(tokens[4]);

                vm.init(pages, frames, pageSize);
            }
            else if (tokens[1] == "policy") {
                vm.setPolicy(tokens[2]);
            }
            else if (tokens[1] == "access") {
                int virtualAddr=stoi(tokens[2]);
                int physicalAddr=vm.access(virtualAddr);

                cout << "Accessing cache with Physical Address " << physicalAddr << endl;
                if (!cacheL1.access(physicalAddr)) {
                    cout<<"L1 MISS"<<endl;
                    if (!cacheL2.access(physicalAddr)) {
                        cout<<"L2 MISS Accessing Main Memory"<<endl;
                        cacheL2.insert(physicalAddr);
                    }
                    else{
                        cout<<"L2 HIT"<<endl;
                    }
                    cacheL1.insert(physicalAddr);
                }
                else{
                    cout<<"L1 HIT"<<endl;
                }
            }
            else if (tokens[1] == "pagetable") {
                vm.printPageTable(); 
            }
            else if (tokens[1] == "stats") {
                vm.stats();
            }
        }

        // ---------- unknown ----------
        else {
            cout << "Unknown command" << endl;
        }
    }

    if (allocator)
        delete allocator;

    return 0;
}

