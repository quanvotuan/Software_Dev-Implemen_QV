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

    CHECK(p_UTString) = SIGNATURE; // Signature
    return p_UTString; // Return the p-> UT String
}

/*
 * Reverses the string in s.
 * Null and check should remain in the same location.
 * Only reverse everything before the \0.
 */
UTString* utstrrev(UTString* s) {
    return NULL;
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    return NULL;
}

/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    return NULL;
}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
    
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
    return NULL;
}


/*
 * Personal Note:
 * UTString  p2; I need to declare it = Set UTString -> p2;
 *
 * // Good Practice: sizeof(<data type>)
 *
 */