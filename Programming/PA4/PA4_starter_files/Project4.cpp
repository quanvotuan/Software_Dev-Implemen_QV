/* 
 * EE312 Simple CRM Project
 *
 * NAME: Quan Tuan Vo
 * EID: qtv73
 */

#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS]; // Customer struct

// Global vars
int num_customers = 0;
int num_books = 0;
int num_dice = 0;
int num_figures = 0;
int num_towers = 0;


/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */


/* clear the inventory and reset the customer database to empty */
void reset(void) {
	/* your code here */
}

void processSummarize() {
    // The summary should first display, the number of Books, Dice, Figures, Towers remaining in inventory at the time of the Summarize command.
    printf("-------------------------\n");
    printf("There are %d Books ", num_books);
    printf("%d Dice ", num_dice);
    printf("%d Figures ", num_figures);
    printf("%d Towers in inventory", num_towers);

}

void processPurchase() {
    // 
}

void processInventory() {
    // read the item type and quantity from the input file and update the store’s inventory of the indicated item type
    String item; // Declare a String datatype = var <name>
    int quantity;
    readString(&item); // Take item -> item
    readNum(&quantity); // Read # of items -> quantity

    // if(quantity > 0){ // *** Asked TAs about negative items ***
    String Books = StringCreate("Books"); // Create a var Book to store the created "Books" string -> Use to compare
    String Dice = StringCreate("Dice");
    String Figures = StringCreate("Figures");
    String Tower = StringCreate("Towers");

    if(StringIsEqualTo(&item, &Books)){
        num_books += quantity; // Updating the store inventory
    }
    else if(StringIsEqualTo(&item, &Dice)){
        num_dice += quantity; // Updating the store inventory
    }
    else if(StringIsEqualTo(&item, &Figures)){
        num_figures += quantity; // Updating the store inventory
    }
    else if(StringIsEqualTo(&item, &Tower)){
        num_towers += quantity; // Updating the store inventory
    }

}
