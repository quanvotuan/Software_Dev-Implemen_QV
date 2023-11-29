#include "MyMemoryController.hpp"

#define NUM_BYTES 10

int test_main() {
    /* 
     * Very basic test of malloc for MyMemoryController
     * You should add more tests to thoroughly test your code
    */
    MyMemoryController* mem = new MyMemoryController(0x2000, 128);
    uint32_t ptr = mem->malloc(NUM_BYTES);
    
    for(int i = 0; i < NUM_BYTES; i++) {
        mem->write(ptr + i, vector<int8_t>(1, i));
    }
    mem->print_heap(0x2000, 0x2014);
    assert(mem->read(ptr-4, 1)[0] == -NUM_BYTES);

    for(int i = 0; i < NUM_BYTES; i++) {
        assert(mem->read(ptr + i, 1)[0] == i);
    }
    mem->free(ptr);
    mem->print_heap(0x2000, 0x2080);
    delete mem;
    return 0;
}