#include "MyMemoryController.hpp"
#include <cstdint>


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
     */

    // Read the content of the base_address
    uint32_t curr_address = base_address;
    uint32_t user_ptr = 0;
    size_t total_byte = heap->get_total_bytes();
    uint32_t buffer = divisibleby4(size);

    /*
    * If there are no blocks of memory greater than or equal to the requested size,
    * return 0 (even if the sum of the sizes of the free memory blocks is greater).
    */

    // Check for allocation
    while (true) {
        if(curr_address >= (base_address + total_byte) || size == 0){ // If curr_address reach the end or size = 0 -> return 0;
            return 0;
        }

        int32_t free_spaces = this->read_full_word(curr_address);
        if ((free_spaces - (int)size) >= 0) { // If there are space -> Allocated space
            int32_t new_free_spaces = free_spaces - buffer - 8; // Update free_spaces
            this->write(curr_address, word_to_bytes(-size)); // Write to the headers -> -size
            this->write(curr_address + (buffer + 4), word_to_bytes(-size)); // Write to the footer -> -size

            // Update the total free spaces
            if(new_free_spaces >= 0){
                this->write(curr_address + (buffer + 8), word_to_bytes(new_free_spaces)); // Write to the header -> nfs
                this->write(curr_address + (buffer + 12 + new_free_spaces),word_to_bytes(new_free_spaces)); // Write to the footer -> nfs
            }
            else if(new_free_spaces == -4){
                this->write(curr_address + buffer + 8, word_to_bytes(0));
            }
            user_ptr = curr_address + 4;

            return user_ptr;
        }

        else { // else jump to next header
            uint32_t next_header = curr_address + divisibleby4(abs(free_spaces)) + 8;
            curr_address = next_header;
        }
    }
}

/*
 * TODO: Implement this method
 *
 * Goal: Frees a block of memory at the given pointer
 *
 * (Done) 1. If the pointer is 0, this method should do nothing.
 * You do not need to check if the pointer being freed is valid; it is the user's responsibility to ensure that
 * However, you should check if the pointer is within the memory system's range and return straight away if it is not
 *
 * (Done) 2. Should write the positive size of the block at the start and end of the block
 * Remember that the pointer passed in is the first address the user can write to,
 * which is not the same as the start of the block of memory you allocated.
 *
 * 3. Remember to merge the new free block with the next free block if possible
 *
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
    uint32_t curr_address = ptr;
    size_t total_byte = heap->get_total_bytes();
    // top_bound = base_address
    uint32_t bot_bound = base_address + total_byte;

    if(ptr == 0){
        return;
    }

    assert(ptr < bot_bound && ptr >= base_address);

    // Free
    uint32_t curr_header = ptr-4; // go to the header
    int32_t curr_spaces = this->read_full_word(curr_header); // Read the curr_spaces
    uint32_t curr_buffer = divisibleby4(-curr_spaces); // Negate to get the buffer
    uint32_t curr_footer = curr_header + curr_buffer + 4;

    this->write(curr_header, word_to_bytes(curr_buffer)); // Write to the headers -> negative curr_spaces
    this->write(curr_footer, word_to_bytes(curr_buffer)); // Write to the footer -> curr_spaces

    // Check Merge:
    // Can I go down?
    uint32_t next_header = curr_header + curr_buffer + 8; // Go to next block header
    if(next_header < bot_bound){ // Find the next header
        int32_t next_spaces = this->read_full_word(next_header); // Read the next_head data
        if(next_spaces >= 0){ // if so merge
            uint32_t next_buffer = divisibleby4(abs(next_spaces)); // Get the buffer
            uint32_t next_footer = (next_header + next_buffer + 4);
            uint32_t merge_buffer = (curr_buffer + next_buffer + 8);
            this->merge(curr_header, next_footer, merge_buffer);
            curr_buffer = merge_buffer; // Update curr_buffer
            curr_footer = next_footer; // Update curr_header
        }
    }
    // Can I go up?
    if (curr_header != base_address){
        uint32_t pre_footer = curr_header - 4; // Go to pre block header
        int32_t pre_spaces = this->read_full_word(pre_footer); // Read the header data

        if(pre_spaces >= 0){
            uint32_t pre_buffer = divisibleby4(abs(pre_spaces)); // Negate to get the buffer
            uint32_t pre_header = (pre_footer - pre_buffer - 4); // Found the pre_header
            uint32_t merge_buffer = (curr_buffer + pre_buffer + 8);
            this->merge(pre_header, curr_footer, merge_buffer);
            curr_buffer = merge_buffer; // Update curr_buffer
            curr_header = pre_header; // Update curr_header
        }
    }
}

/*
 * TODO: Implement this method
 *
 * Reallocates a block of memory of the given size at the given pointer. Returns 0 if the allocation fails.
 * (Done) If the pointer is 0, this method should behave like malloc.
 * (Done) If the size is 0, this method should behave like free (and return 0).
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
    uint32_t curr_address = base_address;
    size_t total_byte = heap->get_total_bytes();
    uint32_t bot_bound = base_address + total_byte;

    assert(ptr < bot_bound && ptr >= base_address);

    if (ptr == 0) {
        uint32_t user_ptr = this->malloc(new_size); // Behave like malloc
        return user_ptr;
    }

    if (new_size == 0){
        this->free(ptr); // Behave like free
        return 0;
    }

    // Find the original size
    uint32_t curr_header = ptr-4; // go to the header
    int32_t curr_spaces = this->read_full_word(curr_header); // Get the curr_spaces
    uint32_t curr_buffer = divisibleby4(-curr_spaces); // Negate curr_spaces to get the buffer = size
    uint32_t curr_footer = curr_header + curr_buffer + 4;

    // Shrinking: Note: curr_head -> shrunk_buffer -> shrunk footer | free_head -> new_space -> curr_footer
    if(new_size <= curr_buffer){
        uint32_t shrunk_buffer = divisibleby4(new_size);
        uint32_t shrunk_footer = (curr_header + 4 + shrunk_buffer); // Create a new_curr_footer
        this->write(curr_header, word_to_bytes(-new_size)); // Shrinking
        this->write(shrunk_footer, word_to_bytes(-new_size)); // Shrinking

        uint32_t free_header = shrunk_footer + 4;
        int32_t new_buffer = curr_footer - (free_header+4); // Compute the new free block
        if(new_buffer == -8){ // If the buffer left after shrink is only 8 bytes -> write 0 to each
            // Do nothing
            std::cout << "Nothing I can do" << std::endl;
        }
        else if(new_buffer == -4){
            this->write(free_header, word_to_bytes(0));
            std::cout << "Don't have enough space to reallocate, sorry :))" << std::endl;
        }
        else{ // >= 0
            this->write(free_header, word_to_bytes(-new_buffer));
            this->write(curr_footer, word_to_bytes(-new_buffer));
            free(free_header + 4); // Free the data, not the header
        }
        return ptr;
    }

    // Expand then shrink
    if(new_size > curr_buffer){ // Expand
        uint32_t next_header = curr_header + curr_buffer + 8; // Go to next block header
        int32_t next_spaces = this->read_full_word(next_header); // Read the next_head data
        if(next_header < bot_bound){ // Can I go down?
            if(next_spaces >= 0){ // Are there free space?
                uint32_t next_buffer = divisibleby4(abs(next_spaces)); // Get the buffer w/ negate space
                uint32_t next_footer = (next_header + next_buffer + 4);
                uint32_t merge_buffer = (curr_buffer + next_buffer + 8);
                if(merge_buffer > new_size){ // Is there enough space
                    this->merge(curr_header, next_footer, -merge_buffer);
                    curr_buffer = merge_buffer; // Update curr_buffer
                    curr_footer = next_footer; // Update curr_header
                }
                this->print_heap(0x2000, 0x2040);
                ptr = this->realloc(ptr, new_size); // Shrink
                return ptr;
            }
            // If the new size is larger than the original size but there is not enough space to expand the given block,
            // you should malloc a new block, copy the data over, free the old block, and return the new pointer.
            else{
                uint32_t user_ptr = this->malloc(new_size); // malloc a new free blk

                // If there is no block in the heap large enough to realloc, free the original block and return 0
                if(user_ptr == 0){
                    free(ptr); // Free the original blk
                    return 0;
                }

                uint32_t new_block_header = user_ptr-4; // Copy the data over
                int32_t new_block_spaces = this->read_full_word(new_block_header); // Get the curr_spaces
                uint32_t new_block_buffer = divisibleby4(abs(new_block_spaces)); // Negate new_block_spaces to get the buffer = size
                uint32_t new_block_footer = new_block_header + new_block_buffer + 4;
                for (int i = 0; i < new_block_buffer; i++) { // copy the data (size = buffer) over
                    int32_t temp = read_full_word(ptr + i);
                    this->write(user_ptr + i, word_to_bytes(temp));
                }

                free(ptr); // free the old block
                return user_ptr;
            }
        }
    }
}