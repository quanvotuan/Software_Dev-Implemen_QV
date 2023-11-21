#ifndef BASE_MEMORY_CONTROLLER_HPP
#define BASE_MEMORY_CONTROLLER_HPP

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>

#include "Heap.hpp"

using namespace std;

/*
 * This class is a generic base class for a memory system. You should not modify this class.
 * You should instead implement the methods in the derived classes 
 * 
 * However, you should read through this class to understand what each variable and method does
 * since they will be needed in the derived classes.
*/

class BaseMemoryController
{
    private:
        vector<pair<uint32_t, uint32_t>> active_blocks; // A vector of pairs of addresses and sizes of active blocks

    public:
        Heap* heap;
        const uint32_t base_address; // The base address of the memory system (i.e. the address of the first byte in memory)
        // These methods are already implemented for you
        BaseMemoryController(uint32_t base_address, uint32_t total_bytes);
        virtual ~BaseMemoryController();
        void reset();
        void print_heap(uint32_t start_address, uint32_t end_address);

        // These are helper methods that you should implement and use
        vector<int8_t> word_to_bytes(uint32_t word);
        int32_t read_full_word(uint32_t address);
        uint32_t divisibleby4(uint32_t n);


        // These virtual methods must be implemented in the derived classes
        virtual vector<int8_t> read(uint32_t address, size_t size);
        virtual void write(uint32_t address, vector<int8_t> data);
        virtual uint32_t malloc(size_t size);
        virtual void free(uint32_t ptr);
        virtual uint32_t realloc(uint32_t ptr, size_t size);

};

#endif