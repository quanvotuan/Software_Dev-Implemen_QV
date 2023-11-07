/*
 * Name: Quan Tuan Vo
 * EID: qtv73
 * PA7
 * Santacruz, Fall 2023
 */
#include <iostream>
#include <cassert>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

// Constructor for Customer
Customer::Customer(UTString name) { // done, please do not edit
    this->books = 0;
    this->dice = 0;
    this->figures = 0;
    this->towers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
} // Constructor for CustomerDB
// Initializes the database with a default capacity of 1 and creates an array of Customer objects on the heap.

int CustomerDB::size(void) { // done, please do not edit
    return this->length; // Return the size of Customers
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data; // Delete the Customers data
}



void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](UTString name) { // not done, your effort goes here
	//TODO
    /*
     * If a Customer in the CustomerDB has a name that matches s,
     * then your function must return that Customer (returning the reference).
     * If there is no Customer in the CustomerDB with that name, then your function must
add the new Customer to the database and return a reference to the newly added Customer.
     */
    if (isMember(name)) {
        for (int i = 0; i < length; ++i) {
            if(data[i].name == name) {
                return data[i];
            }
        }
    }
    // Not found case
        // Check the size if len < cap -> Add | else double size
    if (length < capacity){
        data[length] = Customer(name); // Create a new Customer @ the end
        length++;
    }
    else{
        capacity *= 2; // Update cap
        Customer* new_data = new Customer[capacity]; // Allocate mem

        // Copy old data
        for(int j = 0; j<length; j++){
            new_data[j] = data[j];
        }

        delete[] data;  //Delete old data

        data = new_data; // Update data ptr
        data[length] = Customer(name);// Added new Customer
        length++;
    }
    return data[length-1]; // Return a reference to the added Customer
}

bool CustomerDB::isMember(UTString name) { 
	//TODO
    /*
     * Search through the current set of Customers and returns true
     * if it finds a Customer with the matching name, and returns false otherwise.
     */
    for (int i = 0; i < length; i++) {
        if(data[i].name == name){
            return true; // Found
        }
        return false; // Not Found;
    }
}

/*
 * Questions:
 *  Why do I able to access private variables?
 *
 *  How to add a new Customer -> data base
 *  -> data[length] = Customer(name) // Tell the constructor to build one

    Why do I need to use .c_str()?
    ->


 */
