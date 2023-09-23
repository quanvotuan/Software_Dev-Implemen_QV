// StringADT demonstration file main.cpp
#include <stdio.h>
#include <string.h> // declares the built-in C string library functions, like strcat
#include "UTString.h" // declares our new improved String functions, like utstrcat
#include <stdlib.h>

void testStage1(void) {
    char p[12];
    const char* q = "Hello World";
    UTString* s;
    UTString* t;

    printf("this test should print Hello World three times\n");

    for (unsigned k = 0; k < 12; k += 1) {
        p[k] = q[k];
    }
    s = utstrdup(p);
    printf("%s\n", s->string);

    q = "you goofed!";
    for (unsigned k = 0; k < 12; k += 1) {
        p[k] = q[k];
    }
    printf("%s\n", s->string);

    t = utstrdup(s->string);
    utstrfree(s);
    printf("%s\n", t->string);
    utstrfree(t);
}

void testStage2(void) {
    char c_str1[20] = "hello";
    UTString* ut_str1;
    UTString* ut_str2;

    printf("Starting stage 2 tests\n");
    strcat(c_str1, " world");
    printf("%s\n", c_str1); // nothing exciting, prints "hello world"

    ut_str1 = utstrdup("hello ");
    ut_str1 = utstrrealloc(ut_str1, 20);

    utstrcat(ut_str1, c_str1);
    printf("%s\n", ut_str1->string); // slightly more exciting, prints "hello hello world"
    utstrcat(ut_str1, " world");
    printf("%s\n", ut_str1->string); // exciting, should print "hello hello world wo", 'cause there's not enough room for the second world

    ut_str2 = utstrdup("");
    ut_str2 = utstrrealloc(ut_str2, 11);
    utstrcpy(ut_str2, ut_str1->string + 6);
    printf("%s\n", ut_str2->string); // back to "hello world"

    ut_str2 = utstrrealloc(ut_str2, 23);
    utstrcat(ut_str2, " ");
    utstrcat(ut_str2, ut_str1->string);
    printf("%s\n", ut_str2->string); // now should be "hello world hello hello"

    ut_str1 = utstrrev(ut_str1);
    printf("%s\n", ut_str1->string);
    ut_str2 = utstrrev(ut_str2);
    printf("%s\n", ut_str2->string);

    utstrfree(ut_str1);
    utstrfree(ut_str2);
}

void testStage3(void) {
    int k;
    UTString* ut_str1 = utstrdup("");
    ut_str1 = utstrrealloc(ut_str1, BIG); // big, big string

    printf("attempting stage 3 test. This shouldn't take long...\n");
    printf("(no really, it shouldn't take long, if it does, you fail this test)\n");
    fflush(stdout);

    for (k = 0; k < BIG; k += 1) {
        utstrcat(ut_str1, "*");
    }
    if (ut_str1->string[BIG-1] != '*') {
        printf("stage3 fails for not copying all the characters\n");
    } else if (strlen(ut_str1->string) != BIG) {
        printf("Hmmm, stage3 has something wrong\n");
    } else {
        printf("grats, stage 3 passed (unless it took a long time to print this message)\n");
    }
    utstrfree(ut_str1);
}

#define BAD_SIGNATURE (~0xbaadbeef)

/*
 * This is an important test that likely sounds strange:
 * Each of the following lines should crash the program by failling an assert.
 * Try each, one at a time, to make sure your program acts as expected.
 * If your program does not crash, you are doing something wrong and will lose points.
 */
void testStage4(void) {
    char p[20] = "Hello World!";
    UTString* utstr1 = utstrdup("Hello World");
    *(uint32_t*)( utstr1->string + utstr1->length + 1 ) = BAD_SIGNATURE;
//     printf("crashing with utstrrev\n\n\n"); utstrrev(utstr1);
//     printf("Crashing with utstrcpy\n\n\n"); utstrcpy(utstr1, p);
//     printf("crashing with utstrcat\n\n\n"); utstrcat(utstr1, p);
//     printf("crashing with utstrfree\n\n\n"); utstrfree(utstr1);
//     printf("crashing with utstrrealloc\n\n\n"); utstrrealloc(utstr1, 40);
    free(utstr1->string);
    free(utstr1);
}

void testStage5(void){ // Edge cases test
//    UTString* emptyStr = utstrdup("");
//    printf("Length: %d, Capacity: %d\n", emptyStr->length, emptyStr->capacity);
//    // Expected output: Length: 0, Capacity: 0
//    utstrfree(emptyStr);

    UTString* str = utstrdup("Hello");
    UTString* emptyStr = utstrdup("");
    utstrcat(str, emptyStr->string);
    printf("Result: %s\n", str->string);
// Expected output: Result: Hello
    utstrfree(str);
    utstrfree(emptyStr);
} // Passed

void testStage6(void){
//    UTString* oneCharStr = utstrdup("A");
//    printf("Length: %d, Capacity: %d\n", oneCharStr->length, oneCharStr->capacity);
//// Expected output: Length: 1, Capacity: 1
//    utstrfree(oneCharStr);

    UTString* str = utstrdup("Hello");
    UTString* oneCharStr = utstrdup("X");
    utstrcat(str, oneCharStr->string);
    printf("Result: %s\n", str->string);
// Expected output: Result: HelloX
    utstrfree(str);
    utstrfree(oneCharStr);
}

void testStage7(void){ // Testing with Maximum Allowed Capacity:

//    UTString* maxCapacityStr = utstrdup("This is a long string.");
//    maxCapacityStr = utstrrealloc(maxCapacityStr, UINT32_MAX); // Attempting to set the maximum capacity
//    printf("Length: %d, Capacity: %d\n", maxCapacityStr->length, maxCapacityStr->capacity);
//// Expected output: Length: 22, Capacity: UINT32_MAX
//    utstrfree(maxCapacityStr);

//    UTString* str = utstrdup("Hello");
//    UTString* maxCapacityStr = utstrdup("X");
//    maxCapacityStr = utstrrealloc(maxCapacityStr, UINT32_MAX);
//    utstrcat(str, maxCapacityStr->string);
//    printf("Result: %s\n\n", str->string);
//// Expected output: Result: HelloX
//    utstrfree(str);
//    utstrfree(maxCapacityStr);

}

void testStage8(void){ // Testing with Null Terminator Handling:
    UTString* str = utstrdup("Hello");
    str->capacity += 5; // Inc capa for testing
    char nullTerminatedStr[] = " World";
    utstrcat(str, nullTerminatedStr);
    printf("Result: %s\n", str->string);
// Expected output: Result: Hello World
    utstrfree(str);

//    UTString* str = utstrdup("Hello");
//    char nullTerminatedStr[] = " World";
//    utstrcpy(str, nullTerminatedStr);
//    printf("Result: %s\n", str->string);
//// Expected output: Result:  World
//    utstrfree(str);
}

void testStage9(void){ //Testing with Non-ASCII Characters:
//    UTString* nonAsciiStr = utstrdup("Café");
//    printf("Length: %d, Capacity: %d\n", nonAsciiStr->length, nonAsciiStr->capacity);
//// Expected output: Length: 4, Capacity: 4
//    utstrfree(nonAsciiStr);

    UTString* str = utstrdup("Hello");
    UTString* nonAsciiStr = utstrdup("á");
    utstrcat(str, nonAsciiStr->string);
    printf("Result: %s\n", str->string);
// Expected output: Result: Helloá
    utstrfree(str);
    utstrfree(nonAsciiStr);

}

int main(void) {
    testStage1();
    testStage2();
    testStage3();
    testStage4();
//    testStage5();
//    testStage6();
//    testStage7();
//    testStage8();
//    testStage9();
    return 0;
}



int main1(void){
    char c_str1[20] = "quan_vo";
    UTString* ut_str1;
    UTString* ut_str2;

    UTString* testString = utstrdup(c_str1);
    testString->capacity += 1;
    testString = utstrrev(testString);
    // testString = utstrcat(testString, "quan");
    //testString = utstrcpy(testString, "quan_tuan_vo\0");


    printf("%s\n", testString->string);
    printf("%d\n", testString->length);
    printf("%d", testString->capacity);

    //printf("%s\n", testString->string);

    return 0;

}
