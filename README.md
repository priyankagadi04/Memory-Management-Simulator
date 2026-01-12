# Memory Management Simulator

A C++ based memory management simulator that demonstrates:
- First Fit, Best Fit, Worst Fit allocation
- Buddy System allocation
- Cache simulation (FIFO)
- Virtual Memory with FIFO and LRU page replacement

# Features Implemented
1. Memory Initialization
    Initializes physical memory with a fixed size (e.g., 1024 bytes)
    Prepares memory before any allocation strategy is applied

2. Dynamic Memory Allocation Algorithms
   The simulator supports three classic allocation techniques:
    🔹 First Fit
       Allocates the first free block large enough for the request
       Fast and simple
       Can lead to external fragmentation

    🔹 Best Fit
        Allocates the smallest possible free block
        Reduces wasted memory
        Minimizes external fragmentation

    🔹 Worst Fit
        Allocates the largest available free block
        Avoids small unusable holes
        Demonstrates block merging after free

3. Memory Deallocation & Merging
    Frees allocated blocks using block IDs
    Adjacent free blocks are merged automatically
    Helps reduce fragmentation

4. Memory Dump Visualization
   Displays memory layout after each operation
   Shows:
     Start and end addresses
     USED / FREE blocks
     Allocation IDs
   This makes memory behavior easy to understand visually.

5. Memory Statistics
    The simulator calculates and displays:
       Total memory
       Used memory
       Memory utilization (%)
       Internal fragmentation
       External fragmentation
       Allocation requests, success, and failurerates
    These statistics help compare allocation strategies.

6. Buddy System Allocation
  Allocates memory in powers of two
  Splits memory blocks when required
  Merges buddy blocks on deallocation
  Shows internal fragmentation clearly

7. Cache Memory Simulation
   Multi-Level Cache Support
      L1 Cache (small & fast)
      L2 Cache (larger & slower)
   Cache Features
      Configurable size, line size, associativity
      FIFO replacement policy
      Displays cache hits and misses

8. Virtual Memory Management
   Address Translation
      Converts virtual addresses to physical addresses
      Shows page number, frame number, and physical address
   Page Replacement Policies
      FIFO (First In First Out)
      LRU (Least Recently Used)
   Virtual Memory Statistics
      Total accesses
      Page faults

# Video Demo
 https://1drv.ms/v/c/097d0c298a84ec05/IQBSQ0QtFbzsS7MBUoxNKEz-AfuGf-qLNoKpOQQZPu65lnE?e=WmvvV9

## How to Compile
g++ -std=c++17 src/main.cpp src/allocator/*.cpp src/buddy/*.cpp src/cache/*.cpp src/virtual_memory/*.cpp -I include -o memsim

## How to Run
Get-Content tests/memory_test.txt | ./memsim
