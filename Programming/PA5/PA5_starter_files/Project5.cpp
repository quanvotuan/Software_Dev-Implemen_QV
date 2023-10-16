// Set <Project5.cpp>
// ECE 312 Project 5 submission by
// <Your Name Here>
// <Your EID>
// Slip days used: <0>
// Fall 2023

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }

    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {

    int start = 0;
    int end = self->len - 1;

    while (start <= end) {
        int mid = (start + end) / 2;

        if (self->elements[mid] == x) {
            return true;
        }

        if (x < self->elements[mid]) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return false;
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    if(isMemberSet(self, x)){
        return;
    }

    // Resize the elements arr
    self->elements = (int*) realloc(self->elements, sizeof(int)*(self->len+1));

    if(self->len == 0){
        self->elements[0] = x;
        self->len++;
        return;
    }

    // if x < elem[i]
    if(x < self->elements[0]){
        // Shift all element > x to the right
        for (int j = self->len-1; j >= 0; j--) { // if index j > index i -> shift the end
            self->elements[j+1] = self->elements[j]; // shifted all element on the left by 1
        }
        self->elements[0] = x;
        self->len++;
        return;
    }


    // if x larger
    if(x > self->elements[self->len-1]){
        self->elements[self->len] = x;
        self->len++;
        return;
    }

    // if x in middle
    for (int i = 0; i < self->len; i++) {
        if(x > self->elements[i] && x < self->elements[i+1]){
            for (int j = self->len-1; j > i; j--) { // if index j > index i -> shift the end
                self->elements[j+1] = self->elements[j]; // shifted all element on the left by 1
            }
            self->elements[i+1] = x;
            self->len++;
            return;
        }
    }
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error) [DONE]
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    // if element x doesn't existed in set or the set is empty -> return nothing
    if(!(isMemberSet(self, x)) || isEmptySet(self)){
        return;
    }
    /*
     * 1. Linear Search for element
     * 2. If elem found
     *      2a. shift all element on the right of elem to left by 1
     * 3. If not found
     *      3a. Do nothing!
     */
    int i, j;
    for (i = 0; i < self->len; i++){
        if(self->elements[i] == x){
            // Shifting elements to the left to remove "x"
            for (j = i; j < self->len - 1; j++) {
                self->elements[j] = self->elements[j+1];
            }
            self->len--; // Update self->length
            return; // Element found
        }
    }
    // Can't find "x"
}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if(self->len != other->len){
        return false; // Diff length -> not equal
    }
    for (int i = 0; i < self->len; i++) {
        if(self->elements[i] != other->elements[i]){ // Is the elem of each set the same
            return false; // Elements are not the same
        }
    }
    return true; // Set are equals
}

/* return true if every element of self is also an element of other */
/*
 * 1. Take 1st ele in self, traverse it through other
 * 2. Check whether it existed within other
 *      2a. If yes -> return true
 *      2b. If no -> return false
 */
bool isSubsetOf(const Set* self, const Set* other) {
    if(isEmptySet(self)){ // Based case 1: Empty set is always a subset
        return true;
    }
    if(self->len > other->len){ // Base case 2: Len(self) > Len(other) -> Can't be a subset
        return false;
    }

    int i = 0, j = 0;

    while(i < self->len) {
        if(j == other->len){
            return false; // Self is NOT a subset of other
        }
        // if *i < *j -> inc i
        else if(self->elements[i] < other->elements[j]){
            i++;
        }
        // if *i == *j ->
        else if(self->elements[i] == other->elements[j]){
            i++;
            j++;
        }
        else if(self->elements[i] > other->elements[j]){
            j++;
        }
    }
    return true; // Self is subset of other
}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    /*TODO: Implement 3 pointers
     * 1. i pointer traverse through self
     * 2. j traverse through other
     * 3. k tracker pointer in self
     */

    int i = 0, j = 0, k =0;

    while(i < self->len) {
        if(j == other->len){
            break;
        }
        else if(self->elements[i] < other->elements[j]){
            i++;
        }
        else if(self->elements[i] == other->elements[j]){
            self->elements[k] = self->elements[i];
            k++;
            i++;
        }
        else if(self->elements[i] > other->elements[j]){
            j++;
        }
    }
    self->len = k;
}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    /*TODO:
     * 1. i pointer traverse through self
     * 2. j traverse through other
     * 3. k tracker pointer in self
     */

    int i = 0, j = 0, k =0;

    while(i < self->len) {
        // if j reach the end, push it up, inc i and k
        if(j == other->len){
            // Push it up
            self->elements[k] = self->elements[i];
            i++;
            k++;
        }
        // self->elem is not in other, keep it in the result
        else if(self->elements[i] < other->elements[j]){
            self->elements[k] = self->elements[i];
            i++;
            k++;
        }
        // self->elem == other->elem, skip them
        else if(self->elements[i] == other->elements[j]){
            i++;
            j++;
        }
        // other->elem is not in self, j++
        else if(self->elements[i] > other->elements[j]){
            j++;
        }
    }
    self->len = k;
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    /*TODO:
     * 1. Realloc the size of both self and other-> len combine * int
     * 1. Looking over the self set -> make sure there
     *      for each index of other, traverse through self -> make sure no duplicate
     * 2. use the Logic of InsertSet -> added element into self
     *
     */

    int* merge = (int*) malloc(sizeof(int)*(self->len + other->len));

    int i = 0, j = 0, k =0;

    // Watch what if one array at the end

    while(i != self->len || j != other->len){
        // When i reach the end
        if(i == self->len){
            merge[k] = other->elements[j];
            k++;
            j++;
        }
        // When j reach the end
        else if(j == other->len){
            merge[k] = self->elements[i];
            k++;
            i++;
        }

        // 1st case: if elem[i] == elem[j] -> move i and j++
        else if(self->elements[i] == other->elements[j]){
            merge[k] = self->elements[i];
            k++;
            i++;
            j++;

        }
        // 2nd case: if elem[i] < elem[j] -> put elem[i] -> merge[k]
        else if(self->elements[i] < other->elements[j]){
            merge[k] = self->elements[i];
            k++;
            i++;
        }
        // 3rd case: if elem[i] > elem[j] -> put elem[j] -> merge[k]
        else if(self->elements[i] > other->elements[j]) {
            merge[k] = other->elements[j];
            k++;
            j++;
        }
    }
    self->len = k;
    self->elements = merge;
}
