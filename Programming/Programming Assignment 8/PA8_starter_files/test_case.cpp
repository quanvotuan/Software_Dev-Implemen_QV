#include "MyMemoryController.hpp"

#define NUM_BYTES 10

int main() {
    MyMemoryController* mem = new MyMemoryController(0x2000, 0x00000015);

    vector<int8_t> test1 = mem->read(0x2000, 10);
    int test = mem->read_full_word(0x2000);


//    uint32_t ptr = mem->malloc(NUM_BYTES);
//
//    for(int i = 0; i < NUM_BYTES; i++) {
//        assert (mem->read(ptr + i, 1)[0] == i);
//    }
//    mem->free(ptr);
//    mem->print_heap(0x2000, 0x2014);
//    return 0;

//    mem->print_heap(0x2000, 0x2014);
//    printf("%d", test);
    printf("%d", test1);
}