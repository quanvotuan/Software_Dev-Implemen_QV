#include "MyMemoryController.hpp"

#define NUM_BYTES 10

int main() {
    MyMemoryController* mem = new MyMemoryController(0x2000, 64);

    uint32_t  mem1 = mem->malloc(16);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "----------------------------------" << std::endl;


    uint32_t  mem2 = mem->malloc(20);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "----------------------------------" << std::endl;


    mem1 = mem->realloc(mem1, 15);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "----------------------------------" << std::endl;


    mem2 = mem->realloc(mem2, 24);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "----------------------------------" << std::endl;

    mem->free(mem1);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "----------------------------------" << std::endl;

    mem->free(mem2);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "----------------------------------" << std::endl;



}
