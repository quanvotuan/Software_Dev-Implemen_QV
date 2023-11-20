#include "MyMemoryController.hpp"

/*
 * MyMemoryController constructor. Calls the MemoryController constructor
 *
 * Done for you. You should not modify this method.
*/
MyMemoryController::MyMemoryController(uint32_t base_address, uint32_t total_bytes) : 
    BaseMemoryController(base_address, total_bytes)
{
    this->write(base_address, word_to_bytes(total_bytes-8)); // Write the size of the block at the start and end of the block
    this->write(base_address+total_bytes-4, word_to_bytes(total_bytes-8)); // -8 because we need to account for the size of the metadata
    return;
}

/*
 * MyMemoryController destructor. Calls the MemoryController destructor
 *
 * Done for you. You should not modify this method.
*/
MyMemoryController::~MyMemoryController()
{
    return;
}

/*
 * TODO: Implement this method
 * 
 * Reads 'size' consecutive bytes from memory
 *  -> How?
 *  -> A for loop to go through each individual bytes from memory w/ < size
 *
 * We do not need to check if the addresses being read from are valid; it is the user's responsibility to ensure that
 * @param address: The starting address to read from
 * @param size: The number of bytes to read
 * @return: A vector of bytes read from memory in little endian order (byte at smallest address first)
 *
*/
vector<int8_t> BaseMemoryController::read(uint32_t address, size_t size)
{
    vector<int8_t> new_vect; // Create an empty vector
    int8_t single_byte;

    for (uint32_t i = 0; i < size; i++) {
        single_byte = this->heap->read(address + i); // Store the data on the Heap
        new_vect.push_back(single_byte); // Read all the data and store in vect
    }

    return new_vect;
}


/*
 * TODO: Implement this method
 *
 * Writes each byte in data to memory
 * We do not need to check if the addresses being written to are valid; it is the user's responsibility to ensure that
 * @param address: The starting address to write to
 * @param data: A vector of bytes to write to memory in little endian order (byte at smallest address first)
*/
void BaseMemoryController::write(uint32_t address, vector<int8_t> data)
{
    for (uint32_t i = 0; i < data.size(); i++) {
        this->heap->write(address + i, data[i]); // Write the data -> HEAP
    }
}

/*
 * TODO: Implement this method
 *
 * 1. Allocates a block of memory of the given size at the smallest possible address. Returns 0 if the allocation fails.
 * 2. Should write the negative size of the block at the start and end of the block
 * 3. Remember the returned pointer is the first address the user can write to,
 * 4. which is not the same as the start of the block of memory you allocate.
 * @param size: The number of bytes to allocate
 * @return: A pointer to the start of the allocated block of memory
*/
uint32_t BaseMemoryController::malloc(size_t size)
{
    /*
     * If there are no blocks of memory greater than or equal to the
requested size, return 0 (even if the sum of the sizes of the free memory blocks is greater)
     * You will still need the metadata to hold the true value, but the
size itself may be different, similar to the 37-byte block
     */
    return 0;
}

/*
 * TODO: Implement this method
 *
 * Frees a block of memory at the given pointer
 * If the pointer is 0, this method should do nothing.
 * Should write the positive size of the block at the start and end of the block
 * You do not need to check if the pointer being freed is valid; it is the user's responsibility to ensure that
 * However, you should check if the pointer is within the memory system's range and return straight away if it is not
 * Remember that the pointer passed in is the first address the user can write to,
 * which is not the same as the start of the block of memory you allocated.
 * Remember to merge the new free block with the next free block if possible
 * @param ptr: The pointer to the block of memory to free
 *
 * Note:
 * Check top and bottom of the space I want to free
 * If there are "Free" then merge
 * Else leave it
 *
 * While I haven't reach an allocated space in memory
 * -> Create a counter to keep track of it
 * Until we reach an allocated space -> then add them together into 1 chunk of memory
 *
 *
*/
void BaseMemoryController::free(uint32_t ptr)
{
    return;
}

/*
 * TODO: Implement this method
 *
 * Reallocates a block of memory of the given size at the given pointer. Returns 0 if the allocation fails.
 * If the pointer is 0, this method should behave like malloc.
 * If the size is 0, this method should behave like free (and return 0).
 * If there is enough space to expand the block at the given pointer, you must do so.
 * Remember to copy the data from the old block of memory to the new block of memory if the pointer changes.
 * Remember the returned pointer is the first address the user can write to,
 * which is not the same as the start of the block of memory you allocated.
 * Remember to merge the new free block with the next free block if possible
 * You do not need to check if the pointer being reallocated is valid; it is the user's responsibility to ensure that
 * @param ptr: The pointer to the block of memory to reallocate
 * @param size: The new size of the block of memory
*/
uint32_t BaseMemoryController::realloc(uint32_t ptr, size_t new_size)
{
    return ptr;
}
