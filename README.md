# Memory Management Simulator

A C++ based memory management simulator that demonstrates:
- First Fit, Best Fit, Worst Fit allocation
- Buddy System allocation
- Cache simulation (FIFO)
- Virtual Memory with FIFO and LRU page replacement

## Features
- Physical memory allocation strategies
- Buddy allocator
- Cache hit/miss simulation
- Virtual memory page replacement
- Script-based input using test files

## How to Compile
```bash
g++ -std=c++17 src/main.cpp src/allocator/*.cpp src/buddy/*.cpp src/cache/*.cpp src/virtual_memory/*.cpp -I include -o memsim

## How to Run
Get-Content tests/memory_test.txt | ./memsim
