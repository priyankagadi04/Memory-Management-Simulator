#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


#include "../include/allocator/Allocator.h"
#include "../include/allocator/firstfit.h"
#include "../include/allocator/bestfit.h"
#include "../include/allocator/worstfit.h"
#include "../include/buddy/BuddyAllocator.h"
#include "../include/cache/cache.h"
#include "../include/virtual_memory/virtualmemory.h"
using namespace std;

int main() {
    Allocator* allocator = nullptr;
    BuddyAllocator* buddy = nullptr;
    Cache cache;
    VirtualMemory vm;

    size_t totalMemory = 0;

    string line;
    while (getline(cin, line)) {

        // Ignore empty lines & comments
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        vector<string> tokens;
        string word;

        while (ss >> word) tokens.push_back(word);
        if (tokens.empty()) continue;

        // ---------------- INIT MEMORY ----------------
        if (tokens[0] == "init" && tokens[1] == "memory") {
            totalMemory = stoi(tokens[2]);
            cout << "Physical memory initialized: " << totalMemory << endl;
        }

        // ---------------- SET ALLOCATOR ----------------
        else if (tokens[0] == "set" && tokens[1] == "allocator") {
            delete allocator;
            allocator = nullptr;

            if (tokens[2] == "first_fit") {
                allocator = new firstfit(totalMemory);
                cout << "Allocator set to First Fit\n";
            } 
            else if (tokens[2] == "best_fit") {
                allocator = new bestfit(totalMemory);
                cout << "Allocator set to Best Fit\n";
            } 
            else if (tokens[2] == "worst_fit") {
                allocator = new WorstFit(totalMemory);
                cout << "Allocator set to Worst Fit\n";
            } 
            else if (tokens[2] == "buddy") {
                delete buddy;
                buddy = new BuddyAllocator(totalMemory);
                cout << "Allocator set to Buddy System\n";
            }
        }

        // ---------------- MALLOC ----------------
        else if (tokens[0] == "malloc") {
            size_t size = stoi(tokens[1]);
            if (allocator)
                allocator->allocate(size);
            else if (buddy)
                buddy->allocate(size);
        }

        // ---------------- FREE ----------------
        else if (tokens[0] == "free") {
            int id = stoi(tokens[1]);
            if (allocator)
                allocator->deallocate(id);
            else if (buddy)
                buddy->deallocate(id);
        }

        // ---------------- DUMP ----------------
        else if (tokens[0] == "dump" && tokens[1] == "memory") {
            if (allocator)
                allocator->dump();
            else if (buddy)
                buddy->dump();
        }

        // ---------------- STATS ----------------
        else if (tokens[0] == "stats") {
            if (allocator)
                allocator->stats();
            else if (buddy)
                buddy->stats();
        }

        // ---------------- CACHE ----------------
        else if (tokens[0] == "cache") {
            if (tokens[1] == "init")
                cache.init(tokens[2], stoi(tokens[3]), stoi(tokens[4]), tokens[5]);
            else if (tokens[1] == "access")
                cache.access(tokens[2]);
            else if (tokens[1] == "stats")
                cache.stats();
        }

        // ---------------- VIRTUAL MEMORY ----------------
        else if (tokens[0] == "vm") {
            if (tokens[1] == "init")
                vm.init(stoi(tokens[2]), stoi(tokens[3]), stoi(tokens[4]));
            else if (tokens[1] == "policy")
                vm.setPolicy(tokens[2]);
            else if (tokens[1] == "access")
                vm.access(tokens[2]);
            else if (tokens[1] == "stats")
                vm.stats();
        }
    }

    delete allocator;
    delete buddy;
    return 0;
}