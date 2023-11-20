/*
 * Name: Quan Tuan Vo
 * EID: qtv73
 * PA7
 * Santacruz, Fall 2023
 */

#include <stdio.h>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>

void readString(UTString&);
void readNum(int&);

CustomerDB database;

int num_books = 0;
int num_dice = 0;
int num_figures = 0;
int num_towers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_books = 0;
    num_dice = 0;
    num_figures = 0;
    num_towers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Books", "Dice", "Figures" or "Towers"
 * for example the expression *selectInventItem("Books") returns the
 * current global variable for the number of books in the inventory
 */
int* selectInventItem(UTString word) {
    if (word == "Books") {
        return &num_books;
    } else if (word == "Dice") {
        return &num_dice;
    } else if (word == "Figures") {
        return &num_figures;
    } else if (word == "Towers"){
        return &num_towers;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(UTString word, Customer& cust) {
    if (word == "Books") {
        return &cust.books;
    } else if (word == "Dice") {
        return &cust.dice;
    } else if (word == "Figures") {
        return &cust.figures;
    } else if (word == "Towers"){
        return &cust.towers;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Books", "Dice", "Figures" or "Towers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(UTString type) {
    Customer* result = 0;
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}

void processPurchase() {
    //TODO
    /*

 * This function should read the customer’s name, the item type and the quantity.
 * The function should look up the customer in the customer database (creating a new customer record
 * if this is a 1st-time customer) and increment the number of items purchased by this customer in their customer record.
 *
 * For example, if the customer record indicates that “Frank” had previously purchased
 * 10 dice and the current command indicates that “Frank” is purchasing 20 dice, then the customer record
 * should be set to indicate that 30 dice have been purchased by Frank. Note that each customer should
 * have their own customer record (so that the innkeeper can keep track of who their best customers are and offer incentives like coupons and things).

 */

// Getting input
    UTString customerName;
    UTString itemType;
    int quantity;
    int i;

    // Accessing the var
    readString(customerName); // Read customer variable name -> Craig
    readString(itemType); // Read item name
    readNum(quantity); // Read # of items -> quantity

    // Is this a new customer?
    Customer& customer = database[customerName];

    //if buy quantity == 0, do nothing
    if(quantity == 0){
        return;
    }

    // Update the customer's record with the item purchase
    int* itemInventory = selectInventItem(itemType, customer);
    if(*selectInventItem(itemType) >= quantity){ // If there are more item in Inventory > asked to sell
        *selectInventItem(itemType) -= *selectInventItem(itemType) - quantity; // Update the inventory
        *selectInventItem(itemType, customer) += quantity; // Update the item of Cusomer
    }
    else{ // If Invent item < asked to sell => sorry msg
        std::cout << "Sorry " << customerName.c_str() << ", we only have " << *selectInventItem(itemType) << " " << itemType.c_str() << std::endl;
    }

    // Destroy the string I created
    // -> Already taken care for me by UTString destructor
}

void processSummarize() {
    /*
 * Goal: Print out a summary.
 * 1. display the number of Books, Dice, Figures, Towers remaining in inventory at the time of the Summarize command.
 * 2. display how many different customers have come to the store for purchases.
 * 3. the summary should report which customer purchased the most dice (and how many dice), who purchased the most books (and how many), who purchased the most figures (and how
many), and who purchased the most towers (and how many towers). If a certain item has not been purchased by anybody, then the summary should indicate that. You are provided with three input
files. At the end of each file (after the Quit command) is a transcript of what the output should be
from the Summary command. Please format your output exactly as shown in the file.
 */

    // How to find max?

    // Find max for each item & max_owners
    UTString Books;
    UTString Dice;
    UTString Figures;
    UTString Towers;

    std::cout << "There are " << num_books << " Books " << num_dice << " Dice " << num_figures << " Figures and " << num_towers << " Towers in inventory" << std::endl;
    std::cout << "we have had a total of " << database.size() << " different customers" << std::endl;

    // Find who hold the max Books, Dice, Figures, and Towers
    Customer* maxBooks = findMax(Books);
    Customer* maxDice = findMax(Dice);
    Customer* maxFigures = findMax(Figures);
    Customer* maxTowers = findMax(Towers);

    if(maxBooks != NULL){
        std::cout << maxBooks->name.c_str() << " has purchased the most Books (" << maxBooks->books << ")" << std::endl;
    }
    else{
        std::cout << "no one has purchased any Books"<< std::endl;
    }

    if(maxDice != NULL){
        std::cout << maxDice->name.c_str() << " has purchased the most Books (" << maxDice->dice << ")" << std::endl;
    }
    else{
        std::cout << "no one has purchased any Dice"<< std::endl;
    }
    if(maxFigures != NULL){
        std::cout << maxFigures->name.c_str() << " has purchased the most Books (" << maxFigures->books << ")" << std::endl;
    }
    else{
        std::cout << "no one has purchased any Figures"<< std::endl;
    }
    if(maxTowers != NULL){
        std::cout << maxTowers->name.c_str() << " has purchased the most Books (" << maxTowers->books << ")" << std::endl;
    }
    else{
        std::cout << "no one has purchased any Towers"<< std::endl;
    }

}

void processInventory() {
    // TODO
    // read the item type and quantity from the input file and update the store’s inventory of the indicated item type

    // Getting input
    UTString itemType;
    int quantity;

    // Accessing the var
    readString(itemType); // Read item type
    readNum(quantity); // Read # of items -> quantity

    // Check the database
    // Update the store's inventory based on item type and quantity
    int* inventory = selectInventItem(itemType); // Return # of itemType -> inventory
    if (inventory != 0) {
        *inventory += quantity; // Update the quantity of itemType in the inventory
    }

    // Destroy the string I created
    // -> Already taken care for me by UTString destructor
}
