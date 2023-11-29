#include "MyMemoryController.hpp"
#include <iostream>
#include <vector>

// I don't think this is a 10 for the extra credit,
// but based on what you see for other people's tests it could be
// a 10, I know I'm a 10 ;)
// I can't be bothered, there's too many things to test
static int total_cases;
static int passed_cases;

/*
 * General notes about testing
 *
 * malloc and realloc can only look down in memory, free looks down and up
 *
 * Propagation of 0s
 * (A 0 is a header, footer, or header/footer which contains 0 bytes as the size)
 * If malloc creates a 0, it is not mergable
 * If realloc creates a 0, it could be mergable
 * free should eliminate all consecutive zeros
 *
 * realloc tests are low key nasty, I don't think I'm gonna hit every case
 *
 * I can greatly increase the number of test cases by requesting non multiple of 4
 * blocks of memory, but why would I do that when I can just do in one test and
 * assume it works?
 *
 * I don't even check for invalid memory writing, it wouldn't be too hard to
 * implement that but I'm not going to
 */
// Checks if the heap matches the sizes vector
// Just checks meta, will not check memory contents
#define ALIGNMENT 4
#define ALIGN(var) (var += (var % ALIGNMENT) ? ALIGNMENT - var % ALIGNMENT : 0)
#define DEBUG false
int block_check(MyMemoryController *mem, std::vector<int32_t> sizes)
{
    uint32_t ptr;
    int32_t size;

    ptr = mem->base_address;

    for (int s : sizes) {
        if (DEBUG) std::cout << "Checking for size: " << s << std::endl;
        if (ptr > mem->base_address + mem->heap->get_total_bytes()) return 0;
        size = mem->read_full_word(ptr);
        if (DEBUG) std::cout << "Header: " << size << std::endl;
        // Check header
        if (size != s) return 0;
        if (size < 0) size *= -1;
        ptr += 4 + size;
        ALIGN(ptr);
        // Check footer (only if its not 0, otherwise the header is the footer)
        if (size > 0) {
            if (ptr > mem->base_address + mem->heap->get_total_bytes()) return 0;
            size = mem->read_full_word(ptr);
            if (DEBUG) std::cout << "Footer: " << size << std::endl;
            if (size != s) return 0;
            // Move to next header
            ptr += 4;
        }
    }

    if (DEBUG) std::cout << "Check passed" << std::endl;
    return 1;
}

/*
 * Tests very low memory malloc allocations at the end of memory
 * Also tests free to make sure the initial state is restored
 * Also tests to see if alignments work
 */
void malloc_low_mem_tests()
{
    std::vector<int> v {1, 2, 3, 4};


    /*
    // Visual test
    for (int fw : v) {
        std::cout << "MALLOC LOW MEMORY TEST" << std::endl;
        std::cout << "Available words: " << fw << std::endl;

        MyMemoryController *mem = new MyMemoryController(0x2000, fw * 4 + 8);

        std::cout << "Initial: " << std::endl;
        mem->print_heap(0x2000, 0x2000 + fw * 4 + 8);
        std::cout << "After malloc: " << std::endl;
        uint32_t ptr = mem->malloc(1);
        mem->print_heap(0x2000, 0x2000 + fw * 4 + 8);
        std::cout << "After free: " << std::endl;
        mem->free(ptr);
        mem->print_heap(0x2000, 0x2000 + fw * 4 + 8);
        std::cout << "END TEST" << std::endl;

        delete mem;
    }
    */

    // Real tests
    std::vector<int32_t> sol[][2] = {
            {{-1}, {4}},
            {{-1, 0}, {8}},
            {{-1, 0, 0}, {12}},
            {{-1, 4}, {16}}
    };
    for (int m = 1; m <= 4; ++m) { // Different malloc sizes (alignment test)
        for (int i = 0; i < v.size(); ++i) { // The tests
            sol[i][0][0] = -1 * m;
            MyMemoryController *mem = new MyMemoryController(0x2000, v[i] * 4 + 8);

            uint32_t ptr = mem->malloc(m);
            passed_cases += block_check(mem, sol[i][0]);
            ++total_cases;
            mem->free(ptr);
            passed_cases += block_check(mem, sol[i][1]);
            ++total_cases;

            delete mem;
        }
    }
}

void malloc_zero_propagation_test()
{
    // malloc_low_mem_tests already tests propagation at the end of memory
    // This test will test 0 propagation in the middle of memory
    // X (Claimed)
    // - (Free)
    // X (Claimed)
    // First the middle section will be freed to check if it matches the original setup
    // Next the setup is repeated but now the 3rd block will be freed to see if 0s are claimed
    std::vector<int> v {1, 2, 3};
    const int word_size = 4;

    /*
    // Visual tests
    for (int w : v) {
        std::cout << "MALLOC ZERO PROPAGATION TEST (FREE SECOND BLOCK)" << std::endl;
        std::cout << "Available words: " << w << std::endl;

        size_t total_size = 2 * (word_size + 8) + w * word_size + 8;
        MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

        uint32_t ptr1 = mem->malloc(word_size);
        uint32_t ptr2 = mem->malloc(w * word_size);
        uint32_t ptr3 = mem->malloc(word_size);

        std::cout << ">>Pre Initial: " << std::endl;
        mem->print_heap(0x2000, 0x2000 + total_size);

        mem->free(ptr2);
        std::cout << ">>Initial: " << std::endl;
        mem->print_heap(0x2000, 0x2000 + total_size);

        ptr2 = mem->malloc(word_size);
        std::cout << ">>Post malloc: " << std::endl;
        mem->print_heap(0x2000, 0x2000 + total_size);

        mem->free(ptr2);
        std::cout << ">>Post free: " << std::endl;
        mem->print_heap(0x2000, 0x2000 + total_size);

        delete mem;
    }

    for (int w : v) {
        std::cout << "MALLOC ZERO PROPAGATION TEST (FREE THIRD BLOCK)" << std::endl;
        std::cout << "Available words: " << w << std::endl;

        size_t total_size = 2 * (word_size + 8) + w * word_size + 8;
        MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

        uint32_t ptr1 = mem->malloc(word_size);
        uint32_t ptr2 = mem->malloc(w * word_size);
        uint32_t ptr3 = mem->malloc(word_size);

        mem->free(ptr2);
        std::cout << ">>Initial: " << std::endl;
        mem->print_heap(0x2000, 0x2000 + total_size);

        ptr2 = mem->malloc(word_size);
        std::cout << ">>Post malloc: " << std::endl;
        mem->print_heap(0x2000, 0x2000 + total_size);

        mem->free(ptr3);
        std::cout << ">>Post free: " << std::endl;
        mem->print_heap(0x2000, 0x2000 + total_size);

        delete mem;
    }
    */

    // Real tests
    std::vector<int32_t> sola[][2] = {
            {{-4, -4, -4}, {-4, 4, -4}},
            {{-4, -4, 0, -4}, {-4, 8, -4}},
            {{-4, -4, 0, 0, -4}, {-4, 12, -4}},
    };
    for (int i = 0; i < v.size(); ++i) {
        size_t total_size = 2 * (word_size + 8) + v[i] * word_size + 8;
        MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

        uint32_t ptr1 = mem->malloc(word_size);
        uint32_t ptr2 = mem->malloc(v[i] * word_size);
        uint32_t ptr3 = mem->malloc(word_size);

        mem->free(ptr2);

        ptr2 = mem->malloc(word_size);
        passed_cases += block_check(mem, sola[i][0]);
        ++total_cases;

        mem->free(ptr2);
        passed_cases += block_check(mem, sola[i][1]);
        ++total_cases;

        delete mem;
    }

    std::vector<int32_t> solb[][2] = {
            {{-4, -4, -4}, {-4, -4, 4}},
            {{-4, -4, 0, -4}, {-4, -4, 8}},
            {{-4, -4, 0, 0, -4}, {-4, -4, 12}},
    };
    for (int i = 0; i < v.size(); ++i) {
        size_t total_size = 2 * (word_size + 8) + v[i] * word_size + 8;
        MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

        uint32_t ptr1 = mem->malloc(word_size);
        uint32_t ptr2 = mem->malloc(v[i] * word_size);
        uint32_t ptr3 = mem->malloc(word_size);

        mem->free(ptr2);

        ptr2 = mem->malloc(word_size);
        passed_cases += block_check(mem, solb[i][0]);
        ++total_cases;

        mem->free(ptr3);
        passed_cases += block_check(mem, solb[i][1]);
        ++total_cases;

        delete mem;
    }
}

void malloc_fail_tests()
{
    // This can be made more intensive but I can't be bothered
    MyMemoryController *mem = new MyMemoryController(0x2000, 12);
    uint32_t ptr = mem->malloc(8);
    ++total_cases;
    if (ptr == 0) ++passed_cases;
    ptr = mem->malloc(0);
    ++total_cases;
    if (ptr == 0) ++passed_cases;
    delete mem;
}

void malloc_tests()
{
    malloc_low_mem_tests();
    malloc_zero_propagation_test();
    malloc_fail_tests();
}

void realloc_zero_tests()
{
    //std::cout << "REALLOC SHRINK TEST (Claimed block below)" << std::endl;

    int32_t w = 4;
    const int word_size = 4;
    size_t total_size = 2 * (word_size + 8) + w * word_size + 8;
    MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

    uint32_t ptr1 = mem->malloc(word_size);
    uint32_t ptr2 = mem->malloc(w * word_size);
    uint32_t ptr3 = mem->malloc(word_size);

    //std::cout << ">>Initial: " << std::endl;
    //mem->print_heap(0x2000, 0x2000 + total_size);

    std::vector<int32_t> sol[] = {
            {-4, -16, -4},
            {-4, -12, 0, -4},
            {-4, -8, 0, 0, -4},
            {-4, -4, 4, -4},
            {-4, 16, -4}
    };
    // Check initial case
    passed_cases += block_check(mem, sol[0]);
    ++total_cases;
    int i = 1;
    while (w-- > 0) {
        //std::cout << ">>Realloc for " << std::dec << w << std::endl;
        ptr2 = mem->realloc(ptr2, w * word_size);
        //mem->print_heap(0x2000, 0x2000 + total_size);
        passed_cases += block_check(mem, sol[i++]);
        ++total_cases;
    }

    delete mem;
}

void realloc_padding_shrink_test()
{
    size_t total_size = 3 * (4 + 8);
    MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

    uint32_t ptr1 = mem->malloc(4);
    uint32_t ptr2 = mem->malloc(4);
    uint32_t ptr3 = mem->malloc(4);

    // These solutions are backwards to make the loop easier
    std::vector<int32_t> sol[] = {
            {-4, -1, -4},
            {-4, -2, -4},
            {-4, -3, -4},
            {-4, -4, -4}
    };


    for (int i = 4; i >= 1; --i) {
        ptr2 = mem->realloc(ptr2, i);
        passed_cases += block_check(mem, sol[i - 1]);
        ++total_cases;
    }

    delete mem;
}

void realloc_padding_grow_test()
{
    size_t total_size = 3 * (4 + 8);
    MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

    uint32_t ptr1 = mem->malloc(4);
    uint32_t ptr2 = mem->malloc(1);
    uint32_t ptr3 = mem->malloc(4);

    std::vector<int32_t> sol[] = {
            {-4, -2, -4},
            {-4, -3, -4},
            {-4, -4, -4},
    };


    for (int i = 2; i <= 4; ++i) {
        ptr2 = mem->realloc(ptr2, i);
        passed_cases += block_check(mem, sol[i - 2]);
        ++total_cases;
    }

    delete mem;
}

void realloc_merge_grow_test()
{
    std::vector<int32_t> sol[] = {
            {-4, -5, 0, 0},
            {-4, -6, 0, 0},
            {-4, -7, 0, 0},
            {-4, -8, 0, 0},
            {-4, -9, 0},
            {-4, -10, 0},
            {-4, -11, 0},
            {-4, -12, 0},
            {-4, -13},
            {-4, -14},
            {-4, -15},
            {-4, -16},
            {-4, 16} // Free merges both blocks
    };

    for (int i = 0; i < 13; ++i) {
        size_t total_size = 3 * (4 + 8);
        MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

        uint32_t ptr1 = mem->malloc(4);
        uint32_t ptr2 = mem->malloc(4);
        uint32_t ptr3 = mem->malloc(4);


        mem->free(ptr3);

        ptr2 = mem->realloc(ptr2, 5 + i);
        passed_cases += block_check(mem, sol[i]);
        ++total_cases;

        delete mem;
    }
}

// This test is so nasty
void realloc_nasty_test()
{
    // One open 0, make sure it gets claimed
    std::vector<int32_t> sola[] = {
            {-4, -4, 0, -4},
            {-4, -5, -4},
            {-4, -6, -4},
            {-4, -7, -4},
            {-4, -8, -4},
            {-4, 8, -4}
    };
    for (int i = 0; i < 6; ++i) {
        size_t total_size = 12 + 8 + 4 + 4 + 12;
        MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

        uint32_t ptr1 = mem->malloc(4);
        uint32_t ptr2 = mem->malloc(8);
        uint32_t ptr3 = mem->malloc(4);

        ptr2 = mem->realloc(ptr2, 4);

        ptr2 = mem->realloc(ptr2, 4 + i);
        passed_cases += block_check(mem, sola[i]);
        ++total_cases;

        delete mem;
    }

    // Two open 0s, make sure it gets claimed
    std::vector<int32_t> solb[] = {
            {-4, -4, 0, 0, -4},
            {-4, -5, 0, -4},
            {-4, -6, 0, -4},
            {-4, -7, 0, -4},
            {-4, -8, 0, -4},
            {-4, -9, -4},
            {-4, -10, -4},
            {-4, -11, -4},
            {-4, -12, -4},
            {-4, 12, -4}
    };
    for (int i = 0; i < 10; ++i) {
        size_t total_size = 12 + 8 + 4 + 4 + 4 + 12;
        MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

        uint32_t ptr1 = mem->malloc(4);
        uint32_t ptr2 = mem->malloc(12);
        uint32_t ptr3 = mem->malloc(4);

        ptr2 = mem->realloc(ptr2, 4);

        ptr2 = mem->realloc(ptr2, 4 + i);
        passed_cases += block_check(mem, solb[i]);
        ++total_cases;

        delete mem;
    }
}

void realloc_copy_test()
{
    int32_t total_size = 12 + 12 + 12 + 24;
    MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

    uint32_t ptr1 = mem->malloc(4);
    uint32_t ptr2 = mem->malloc(4);
    uint32_t ptr3 = mem->malloc(4);
    //uint32_t ptr4 = mem->malloc(16);

    for(int i = 0; i < 4; i++) {
        mem->write(ptr2 + i, vector<int8_t>(1, i));
    }

    ++total_cases;
    ptr2 = mem->realloc(ptr2, 16);
    for(int i = 0; i < 4; i++) {
        if (mem->read(ptr2 + i, 1)[0] != i) {
            delete mem;
            return;
        }
    }
    ++passed_cases;


    delete mem;
}

void realloc_tests()
{
    realloc_zero_tests();
    realloc_padding_shrink_test();
    realloc_padding_grow_test();
    realloc_merge_grow_test();
    realloc_nasty_test();
    realloc_copy_test();
}

// A few merge tests
// One could do some tests where the ends are malloc'ed blocks
// instead of the ends of memory but that one is not me
void free_simple()
{
    size_t total_size = 3 * (4 + 8);
    MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

    uint32_t ptr1 = mem->malloc(4);
    uint32_t ptr2 = mem->malloc(4);
    uint32_t ptr3 = mem->malloc(4);

    // 1 3 2
    std::vector<int32_t> sol[] = {
            {4, -4, -4},
            {4, -4, 4},
            {28},
    };

    mem->free(ptr1);
    passed_cases += block_check(mem, sol[0]);
    ++total_cases;


    mem->free(ptr3);
    passed_cases += block_check(mem, sol[1]);
    ++total_cases;

    mem->free(ptr2);
    passed_cases += block_check(mem, sol[2]);
    ++total_cases;


    delete mem;

    mem = new MyMemoryController(0x2000, total_size);

    ptr1 = mem->malloc(4);
    ptr2 = mem->malloc(4);
    ptr3 = mem->malloc(4);

    // 1 2 3
    std::vector<int32_t> sola[] = {
            {4, -4, -4},
            {16, -4},
            {28},
    };

    mem->free(ptr1);
    passed_cases += block_check(mem, sola[0]);
    ++total_cases;


    mem->free(ptr2);
    passed_cases += block_check(mem, sola[1]);
    ++total_cases;

    mem->free(ptr3);
    passed_cases += block_check(mem, sola[2]);
    ++total_cases;


    delete mem;

    mem = new MyMemoryController(0x2000, total_size);

    ptr1 = mem->malloc(4);
    ptr2 = mem->malloc(4);
    ptr3 = mem->malloc(4);

    // 3 2 1
    std::vector<int32_t> solb[] = {
            {-4, -4, 4},
            {-4, 16},
            {28},
    };

    mem->free(ptr3);
    passed_cases += block_check(mem, solb[0]);
    ++total_cases;


    mem->free(ptr2);
    passed_cases += block_check(mem, solb[1]);
    ++total_cases;

    mem->free(ptr1);
    passed_cases += block_check(mem, solb[2]);
    ++total_cases;


    delete mem;
}

// Free a middle block with sizes 1,2,3 (4 is already tested in simple)
// Doesn't test merges
void free_padding()
{
    size_t total_size = 3 * (4 + 8);
    MyMemoryController *mem = new MyMemoryController(0x2000, total_size);

    uint32_t ptr1 = mem->malloc(4);
    uint32_t ptr2 = mem->malloc(4);
    uint32_t ptr3 = mem->malloc(4);

    std::vector<int32_t> sol {-4, 4, -4};

    mem->free(ptr2);

    for (int i = 1; i <= 3; ++i) {
        ptr2 = mem->malloc(i);
        mem->free(ptr2);
        passed_cases += block_check(mem, sol);
        ++total_cases;
    }

    delete mem;
}

void free_tests()
{
    free_simple();
    free_padding();
}

int test_main() {
    int score;
    malloc_tests();
    realloc_tests();
    free_tests();

    std::cout << "Mihir's Memory Test Cases" << std::endl;
    std::cout << "Written by the legend himself" << std::endl;

    std::cout << std::endl;

    std::cout << "You passed " << passed_cases << " out of " << total_cases << " cases." << std::endl;

    score = passed_cases * 100 / total_cases;

    if (score > 100) {
        std::cout << "Bruh, how? You exceeded my test cases!!! Hmu." << std::endl;
    }
    else if (score == 100) {
        std::cout << "Okay beast, you passed all my cases. Go and get yourself a cookie or something. (Make sure to touch grass as well)" << std::endl;
    }
    else if (score == 69) {
        std::cout << "How did you get 69? This is probably even harder than getting a 0. You get bragging rights." << std::endl;
    }
    else if (score < 100 && score >= 90) {
        std::cout << "Ok hot stuff, you got about an A on my test cases. I would say that's good enough but if you wanna go for that 100 that's on you." << std::endl;
    }
    else if (score < 90 && score >= 80) {
        std::cout << "You got about a B on my cases. Not bad not bad." << std::endl;
    }
    else if (score < 80 && score >= 70) {
        std::cout << "You got about a C on my cases. Cs get degrees." << std::endl;
    }
    else if (score < 70 && score >= 50) {
        std::cout << "You got at least half of the cases. You got this." << std::endl;
    }
    else if (score < 50 && score >= 25) {
        std::cout << "Only Jason can save you now..." << std::endl;
    }
    else if (score > 0) {
        std::cout << "Dude, I'm not even sure Jason can help you at this point :(" << std::endl;
    }
    else if (score == 0) {
        std::cout << "You somehow managed to fail every single one my test cases without crashing. Honestly impressive, more impressive than getting a 100 in my opinion. Good job, no, great job!" << std::endl;
    }

    return 0;
}