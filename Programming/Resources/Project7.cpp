/*
 * Name: 
 * EID: 
 * PA7
 * Santacruz, Fall 2023
 */

#include <stdio.h>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>

using namespace std;

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
    //get our information into our variables from the user and compare later to what is in storage
    UTString Name;
    UTString item;
    int quantity = 0;
    readString(Name);
    readString(item);
    readNum(quantity);

    if(quantity == 0){
        return;//if quantity is 0 then just return, no use trying
    }
    if(*selectInventItem(item) >= quantity){//if there is more or enough in inventory for the buyer then take it out of the system and assign to buyer
        *selectInventItem(item) = *selectInventItem(item) - quantity;
        *selectInventItem(item, database[Name]) = *selectInventItem(item, database[Name]) + quantity;
    }
    else if(*selectInventItem(item) < quantity){ //if the amount in stock is less than what the buyer needs then return the sorry message
        cout << "Sorry " << Name.c_str() << ", we only have " << *selectInventItem(item) << " " << item.c_str() << endl;
    }
}

void processSummarize() {
    /*TODO:
     * create summary for inventory size and what is available
     * create vars to use findMax function for searching who bought the most of a certain item
     * do comparisons to make sure there are no nulls or 0s when printing most of all items in DB
     * */
    cout << "There are " << num_books << " Books " << num_dice << " Dice " << num_figures << " Figures and " << num_towers << " Towers in inventory" << endl;
    cout << "we have had a total of " << database.size() << " different customers" << endl;

    Customer* mostBooks = findMax("Books");
    Customer* mostDice = findMax("Dice");
    Customer* mostFigures = findMax("Figures");
    Customer* mostTowers = findMax("Towers");

    if(mostBooks != NULL){
        cout << mostBooks->name.c_str() << " has purchased the most Books (" << mostBooks->books << ")" << endl;
    }
    else{
        cout << "no one has purchased any Books"<< endl;
    }
    if(mostDice != NULL){
        cout << mostDice->name.c_str() << " has purchased the most Dice (" << mostDice->dice << ")" << endl;
    }
    else{
        cout << "no one has purchased any Dice"<<endl;
    }
    if(mostFigures != NULL){
        cout << mostFigures->name.c_str() << " has purchased the most Figures (" << mostFigures->figures << ")" << endl;
    }
    else{
        cout << "no one has purchased any Figures"<<endl;
    }
    if(mostTowers != NULL){
        cout << mostTowers->name.c_str() << " has purchased the most Towers (" << mostTowers->towers << ")" << endl;
    }
    else{
        cout << "no one has purchased any Towers"<<endl;
    }
}

void processInventory() {
    /* TODO:
     * get name of item, quantity, and read those contents
     * add quantity to its specified item name
     * */

    UTString item; // create var item using type UTString for item name
    int quantity = 0;//init quantity var to store quantity of item being processsed
    readString(item);//read the name of the item being input and store it in the item var
    readNum(quantity);//read the quantity number from the item inputted and store in the quantity var

    *selectInventItem(item) = *selectInventItem(item) + quantity;//add quantity to selected item quantity
}
