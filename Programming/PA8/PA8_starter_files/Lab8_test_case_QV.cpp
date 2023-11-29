#include "MyMemoryController.hpp"

#define NUM_BYTES 10

int main() {
    MyMemoryController *mem = new MyMemoryController(0x2000, 64);

    std::cout << "---- Test 1 ----" << std::endl;
    mem->print_heap(0x2000, 0x2040);

    int32_t test1 = mem->read_full_word(0x2000);
    std::cout << std::hex << test1 << std::endl;
    std::cout << "1. --------------" << std::endl;

    uint32_t mem1 = mem->malloc(14);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "2. -------------------" << std::endl;

    uint32_t mem2 = mem->malloc(22);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "3. --------------------" << std::endl;

    mem1 = mem->realloc(mem1, 2);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "4. ---------------------" << std::endl;

    mem2 = mem->realloc(mem2, 25);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "5. ---------------------" << std::endl;

    uint32_t mem3 = mem->malloc(16);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "6. --------------------" << std::endl;

    std::cout << "mem3 = " << mem3 << std::endl;

//    mem3 = mem->realloc(mem3, 7);
//    mem->print_heap(0x2000, 0x2040);
//    std::cout << "--------------------" << std::endl;

    mem->free(mem3);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "7. --------------------" << std::endl;

    mem->free(mem1);
    mem->print_heap(0x2000, 0x2040);
    std::cout << "8. -------------------" << std::endl;

    mem->free(mem2);
    mem->print_heap(0x2000, 0x2041);
    std::cout << "9. ---------------------" << std::endl;


    int32_t end_test1 = mem->read_full_word(0x203c);
    std::cout << end_test1 << std::endl;

    // assert(test1 == end_test1); // Check whether the total bytes after free == original heap size

/*
 * Malloc -> Realloc -> Free -> Delete = Work
 * Malloc(m1,m2) -> Realloc (m1,m2) -> Free (m3,m1,m2) -> Delete mem = Work
 */
    delete mem;
}


    // Test 2:
    // ---------------------------------------------------- //

    // Idea to test: Fill up the HEAP

//    int32_t test2 = mem->read_full_word(0x2000);
//
//    std::cout << "---- Test 2 ----" << std::endl;

//    uint32_t mem3 = mem->malloc(5);
//    mem->print_heap(0x2000, 0x2040);
//    std::cout << "----------------------------------" << std::endl;
//
//    mem3 = mem->realloc(mem3, 18);
//    mem->print_heap(0x2000, 0x2040);
//    std::cout << "----------------------------------" << std::endl;
//
//    uint32_t mem4 = mem->malloc(25);
//    mem->print_heap(0x2000, 0x2040);
//    std::cout << "----------------------------------" << std::endl;
//
//    mem4 = mem->realloc(mem4, 9);
//    mem->print_heap(0x2000, 0x2040);
//    std::cout << "----------------------------------" << std::endl;
//
//    mem->free(mem3);
//    mem->print_heap(0x2000, 0x2040);
//    std::cout << "----------------------------------" << std::endl;
//
//    mem->free(mem4);
//    mem->print_heap(0x2000, 0x2040);
//    std::cout << "----------------------------------" << std::endl;
//
//    int32_t end_test2 = mem->read_full_word(0x203c);
//    assert(test1 == end_test1); // Check whether the total bytes after free == original heap size