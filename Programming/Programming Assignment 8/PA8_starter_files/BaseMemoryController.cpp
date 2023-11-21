#include <bitset>
#include "BaseMemoryController.hpp"

/*
 * BaseMemoryController constructor
 * 
 * Done for you. You should not modify this method.
*/
BaseMemoryController::BaseMemoryController(uint32_t base_address, uint32_t total_bytes) :
    base_address(base_address),
    heap(new Heap(base_address, total_bytes))
{
    
}

/*
 * BaseMemoryController destructor
 * 
 * Done for you. You should not modify this method.
*/
BaseMemoryController::~BaseMemoryController()
{
    delete this->heap;
}


/*
 * Resets the memory system
 *
 * Done for you. You should not modify this method.
*/
void BaseMemoryController::reset()
{
    this->heap->reset();
    this->active_blocks.clear();
}

/*
 * Prints out the contents of the heap
 *
 * Done for you. You should not modify this method.
*/
void BaseMemoryController::print_heap(uint32_t start_address, uint32_t end_address)
{
    this->heap->print_heap(start_address, end_address);
}

/*
 * TODO: Implement this method
 *
 * Converts a word (4 bytes) to a vector of bytes in little endian order (byte at smallest address first)
 * For example, if the word is: 0x6053890A,
 * word_to_bytes(0x6053890A) should return {0x0A, 0x89, 0x53, 0x60}
 * 00008900
 *
 * 0. Create an empty vect
 * 1. Mask out the bytes I want
 * 1b) Bit Shift
 * 2. Vector push back the data
 * 3. Return the new vect
*/
vector<int8_t> BaseMemoryController::word_to_bytes(uint32_t word)
{

    vector<int8_t> wtb_vect; // 0.
    uint32_t mask1 = 0x000000FF;
    uint32_t mask2 = 0x0000FF00;
    uint32_t mask3 = 0x00FF0000;
    uint32_t mask4 = 0xFF000000;

    uint32_t first_bytes = word & mask1; // 1. Mask out the bytes
    uint8_t shift_first_bytes = first_bytes;
    wtb_vect.push_back(shift_first_bytes); // 2. Vector push back

    uint32_t seconds_bytes = word & mask2; // 1. Mask out the bytes
    uint8_t shift_seconds_bytes =  seconds_bytes >> 8;
    wtb_vect.push_back(shift_seconds_bytes); // 2. Vector push back

    uint32_t third_bytes = word & mask3; // 1. Mask out the bytes
    uint8_t shift_third_bytes =  third_bytes >> 16;
    wtb_vect.push_back(shift_third_bytes); // 2. Vector push back

    uint32_t fourth_bytes = word & mask4; // 1. Mask out the bytes
    uint8_t shift_fourth_bytes =  fourth_bytes >> 24;
    wtb_vect.push_back(shift_fourth_bytes); // 2. Vector push back

    return wtb_vect;
}

/*
 * TODO: Implement this method
 *
 * Reads a full word (4 bytes) from the memory system
 * For example, if the memory is x2000: 0A 89 53 60,
 * read_full_word(0x2000) should return 0x6053890A
 *
*/
int32_t BaseMemoryController::read_full_word(uint32_t address)
{
    // Same logic, but reverse
    // Remember: Shift bits not bytes

    uint8_t shift_single_byte;
    uint32_t  words = 0;

    // 1. Read the address
    for (uint32_t i = 0; i < 4; i++) {
        int8_t single_byte = this->heap->read(address + i); // Store the data on the Heap
        if(i == 0){
            words += single_byte;
        }
        else if(i > 0){
            shift_single_byte = single_byte << (8 * i);
            words += shift_single_byte;
        }
    }
    return words; // Return the words
}


// Round the nearest number divisible by 4
uint32_t BaseMemoryController::divisibleby4(uint32_t n){
    uint32_t i = n;
    while((i%4) != 0){
        i++;
    }
    return i;
}
