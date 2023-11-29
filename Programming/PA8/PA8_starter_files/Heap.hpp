
/*
 * This class implements a basic Heap block more realistically than just using an array. 
 *
 * Done for you. You should not modify this file.
*/

#ifndef HEAP_HPP
#define HEAP_HPP

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include <iomanip>

using namespace std;


class Heap {

    private:
        int8_t* heap;
        const uint32_t base_address;
        const size_t total_bytes;
        uint32_t num_reads;
    
    public:
        Heap(uint32_t base_address, size_t total_bytes);
        ~Heap();
        void reset();
        int8_t read(uint32_t address);
        void write(uint32_t address, int8_t data);
        uint32_t get_num_reads();
        size_t get_total_bytes();
        void print_heap(uint32_t start_address, uint32_t end_address);
};

#endif