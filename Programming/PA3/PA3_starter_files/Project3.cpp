/**
 * NAME: Quan Tuan Vo
 * EID: qtv73
 * Fall 2023
 * Santacruz
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "UTString.h"

/* QUESTIONS:

     * Why don't I see the Check Key after my String in memory?
     * -> Because it added at the end of the struct
     *
     * How to check whether dst is a valid UTString? *
     * -> use assert(isOurs(<string>))
     *
     * When is DONE?
     * -> When src string = '\0'
     *
     * When does my strcpy broke?
     * -> When adding the Signature (Solved)
     * -> Because SIGNATURE depend on the String length, and I accidentally update the length incorrectly
     *
     * Check over the strrev func?
     * -> Should I use string.h?
     *
     * What happened if string != a valid UTString?
     * ->
     *
     * How to free correctly?
     *
     *

 * Personal Note:
 * UTString  p2; I need to declare it = Set UTString -> p2;
 *
 * // Good Practice: sizeof(<data type>)


*/

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}

/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 * Initially set the capacity equal to the length of the string.
 * Setting the length, capacity, and check appropriately. Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
    // malloc for entire UTString itself
    UTString *p_UTString = (UTString*) malloc (sizeof(UTString)); // sizeof(UTString) = 16 byte
    p_UTString->length = strlen(src);
    p_UTString->capacity = strlen(src); // Set the capacity equal to the length of the string.

    // malloc for char* string itself
    char *p_src = (char*) malloc(sizeof(char) * (strlen(src) + 5)); // Create a p_src -> string within struct UTString | sizeof(char) * # of characters + 5 because of the signature + NULL
    strcpy(p_src,src); // Copy the string -> p_src (NULL included)
    p_UTString->string = p_src; // Set the string from p_src -> p_UTString

    CHECK(p_UTString) = SIGNATURE; // Signature
    return p_UTString; // Return the p-> UT String
}

/*
 * Reverses the string in s.
 * Null and check should remain in the same location.
 * Only reverse everything before the \0.
 */
UTString* utstrrev(UTString* s) {
    strrev(s->string);
    CHECK(s) = SIGNATURE; // This might be not need
    return s;
}

/*
 * Append the string suffix to the UTString s.
 * s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    assert(isOurs(s));

    char* new_string = s->string;
    uint32_t i = s->length; // last index of s
    uint32_t s_length = s->length;
    uint32_t s_capacity = s->capacity;
    char j = 0;

    while(s_length < s_capacity){ // Reach capacity yet?
        new_string[i] = suffix[j];
        if(new_string[i] == '\0'){ // Done append yet?
            break;
        }
        j++;
        i++;
        s_length++; // Update the length of s
    }
    new_string[i] = '\0'; // NULL terminated my string
    s->length = strlen(new_string);
    CHECK(s) = SIGNATURE;
    return s;
}

/*
 * (Done) Copy src into dst.
 *  (???) dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters as will actually fit in dst.
 * (Done) Update the length of dst.
 * (Done) Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    assert(isOurs(dst));
    char* dst_string = dst->string;
    uint32_t dst_capacity = dst->capacity;
    char i = 0; // index

    while(i < dst_capacity){ // Reach capacity yet?
        dst_string[i] = src[i]; // Copying char by char
        if(src[i] == '\0'){ // Done copy yet?
            break;
        }
        i++;
    }

    dst_string[i] = '\0'; // NULL terminated dst_string
    dst->length = strlen(dst_string); // Update the length of dst
    CHECK(dst) = SIGNATURE; // Added SIGNATURE
    return dst; // Return dst with the above changes.
}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
    assert(isOurs(self));
    free(self->string);
    free(self);
}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    assert(isOurs(s));
    if(s->capacity > new_capacity){
        return s; // If s has enough capacity already, do nothing.
    }else{
        // If s does not have enough capacity, then allocate enough capacity
        s->string = (char*) realloc(s->string, new_capacity+5); // Go into s, update the size, copy everything -> store it back to s
        s->capacity = new_capacity; // Update the capa
    }
    return s;

// not using realloc method:
    //    char *p_src = (char*) malloc(sizeof(char) * (new_capacity + 5));
    //    strcpy(p_src, s->string);//
    //    free(s->string);
    //    s->string = p_src;
    //    s->capacity = new_capacity;


    // Create
    // if my length = BIG ->
    // Crete a really big constant
}