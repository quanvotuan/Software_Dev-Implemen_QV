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
    for (int i = 0; i < num_customers; i++) {
        StringDestroy(&customers[i].name);
        customers[i].books = 0;
        customers[i].dice = 0;
        customers[i].figures = 0;
        customers[i].towers = 0;
        customers[i].name.len = 0;
    }

    // Reset all Global Vars
    num_customers = 0;
    num_books = 0;
    num_dice = 0;
    num_figures = 0;
    num_towers = 0;
}

void processSummarize() {
    /*
     * Goal: Print out a summary.
     * (Done) 1. display the number of Books, Dice, Figures, Towers remaining in inventory at the time of the Summarize command.
     * (Done) 2. display how many different customers have come to the store for purchases.
     * () 3. the summary should report which customer purchased the most dice (and how many dice), who purchased the most books (and how many), who purchased the most figures (and how
many), and who purchased the most towers (and how many towers). If a certain item has not been purchased by anybody, then the summary should indicate that. You are provided with three input
files. At the end of each file (after the Quit command) is a transcript of what the output should be
from the Summary command. Please format your output exactly as shown in the file.
     */

    // Find max for each item & max_owners
    int max_books = 0;
    int max_dice = 0;
    int max_figures = 0;
    int max_towers = 0;

    int max_books_owner;
    int max_dice_owner;
    int max_figures_owner;
    int max_towers_owner;

    for (int i = 0; i < num_customers; i++) {
        if(customers[i].books > max_books){
            max_books = customers[i].books;
            max_books_owner = i;
        }
        if(customers[i].dice > max_dice){
            max_dice = customers[i].dice;
            max_dice_owner = i;
        }
        if(customers[i].figures > max_figures){
            max_figures = customers[i].figures;
            max_figures_owner = i;
        }
        if(customers[i].towers > max_towers){
            max_towers = customers[i].towers;
            max_towers_owner = i;
        }
    }

    // Ouput:
    printf("There are %d Books ", num_books);
    printf("%d Dice ", num_dice);
    printf("%d Figures and ", num_figures);
    printf("%d Towers in inventory\n", num_towers);
    printf("we have had a total of %d different customers\n", num_customers);

    if(max_books != 0) {
        StringPrint(&customers[max_books_owner].name);
        printf(" has purchased the most Books (%d)\n", max_books);
    }else{
        printf("no one has purchased any Books\n");
    }

    if(max_dice != 0){
        StringPrint(&customers[max_dice_owner].name);
        printf(" has purchased the most Dice (%d)\n", max_dice);
    }else{
        printf("no one has purchased any Dice\n");
    }

    if(max_figures != 0){
        StringPrint(&customers[max_figures_owner].name);
        printf(" has purchased the most Figures (%d)\n", max_figures);
    }else{
        printf("no one has purchased any Figures\n");
    }

    if(max_towers != 0){
        StringPrint(&customers[max_towers_owner].name);
        printf(" has purchased the most Towers (%d)\n", max_towers);
    }else{
        printf("no one has purchased any Towers\n");
    }
}

void processPurchase() {
    /*
     * (Done) This function should read the customer’s name, the item type and the quantity.
     * (Done) The function should look up the customer in the customer database (creating a new customer record
     * if this is a 1st-time customer) and increment the number of items purchased by this customer in their customer record.
     *
     * For example, if the customer record indicates that “Frank” had previously purchased
     * 10 dice and the current command indicates that “Frank” is purchasing 20 dice, then the customer record
     * should be set to indicate that 30 dice have been purchased by Frank. Note that each customer should
     * have their own customer record (so that the innkeeper can keep track of who their best customers are and offer incentives like coupons and things).

     */

    // Getting input
    String name;
    String item;
    int quantity;
    int i;

    // Create items to compare later
    String Books = StringCreate("Books");
    String Dice = StringCreate("Dice");
    String Figures = StringCreate("Figures");
    String Tower = StringCreate("Towers");

    // Accessing the var
    readString(&name); // Read customer variable name -> Craig
    readString(&item); // Read item name
    readNum(&quantity); // Read # of items -> quantity

    // Check the database
    for (i = 0; i < num_customers; i++) { // Check if the customer exist
        // Check the customer name
        if(StringIsEqualTo(&name, &customers[i].name)){
            // Check the items
            if(StringIsEqualTo(&item, &Books)){
                if(quantity > num_books){
                    printf("Sorry ");
                    StringPrint(&customers[i].name);
                    printf(", we only have %d Books\n", num_books);
                }
                else if(quantity > 0){
                    customers[i].books += quantity; // Updating the Customer's Books inventory
                    num_books -= quantity; // Updating the store inventory
                }
            }
            else if(StringIsEqualTo(&item, &Dice)){
                if(quantity > num_dice){
                    printf("Sorry ");
                    StringPrint(&customers[i].name);
                    printf(", we only have %d Dice\n", num_dice);
                }
                else if(quantity > 0) {
                    customers[i].dice += quantity; // Updating the Customer's Dice inventory
                    num_dice -= quantity; // Updating the store inventory
                }
            }
            else if(StringIsEqualTo(&item, &Figures)){
                if(quantity > num_figures){
                    printf("Sorry ");
                    StringPrint(&customers[i].name);
                    printf(", we only have %d Figures\n", num_figures);
                }
                else if(quantity > 0) {
                    customers[i].figures += quantity; // Updating the Customer's Figures inventory
                    num_figures -= quantity; // Updating the store inventory
                }
            }
            else if(StringIsEqualTo(&item, &Tower)){
                if(quantity > num_towers){
                    printf("Sorry ");
                    StringPrint(&customers[i].name);
                    printf(", we only have %d Towers\n", num_towers);
                }
                else if(quantity > 0) {
                    customers[i].towers += quantity; // Updating the Customer's Tower inventory
                    num_towers -= quantity; // Updating the store inventory
                }
            }
            StringDestroy(&name);
            break; // Break if Customer FOUNDED
        }
    }
    if(i == num_customers && i < MAX_CUSTOMERS){ // Done Searching through the Database -> The Customer doesn't existed

        // Check inventory if we have enough
        if(StringIsEqualTo(&item, &Books)){
            if(quantity > num_books){ // Sorry, we don't have enough item
                printf("Sorry ");
                StringPrint(&name);
                printf(", we only have %d Books\n", num_books);
                StringDestroy(&name);
            }
            else if(quantity > 0){ // Selling
                customers[i].books = quantity; // Updating the Customer's Books inventory
                num_books -= quantity; // Updating the store inventory
                // Added to database
                customers[i].name = name;
                num_customers++;
                StringDestroy(&name);
            }
            else{
                StringDestroy(&name);
            }
        }
        else if(StringIsEqualTo(&item, &Dice)){
            if(quantity > num_dice){
                printf("Sorry ");
                StringPrint(&name);
                printf(", we only have %d Dice\n", num_dice);
                StringDestroy(&name);

            }
            else if(quantity > 0){
                customers[i].dice = quantity; // Updating the Customer's Dice inventory
                num_dice -= quantity; // Updating the store inventory
                // Added to database
                customers[i].name = name;
                num_customers++;
                StringDestroy(&name);
            }
            else{
                StringDestroy(&name);
            }
        }
        else if(StringIsEqualTo(&item, &Figures)){
            if(quantity > num_figures){
                printf("Sorry ");
                StringPrint(&name);
                printf(", we only have %d Figures\n", num_figures);
                StringDestroy(&name);

            }
            else if(quantity > 0){
                customers[i].figures = quantity; // Updating the Customer's Figures inventory
                num_figures -= quantity; // Updating the store inventory
                // Added to database
                customers[i].name = name;
                num_customers++;
                StringDestroy(&name);
            }
            else{
                StringDestroy(&name);
            }
        }
        else if(StringIsEqualTo(&item, &Tower)){
            if(quantity > num_towers){
                printf("Sorry ");
                StringPrint(&name);
                printf(", we only have %d Towers\n", num_towers);
                StringDestroy(&name);

            }
            else if(quantity > 0){
                customers[i].towers = quantity; // Updating the Customer's Tower inventory
                num_towers -= quantity; // Updating the store inventory
                // Added to database
                customers[i].name = name;
                num_customers++;
                StringDestroy(&name);
            }
            else{
                StringDestroy(&name);
            }
        }
    }

    // Destroy all the string I created
    StringDestroy(&Books);
    StringDestroy(&Dice);
    StringDestroy(&Figures);
    StringDestroy(&Tower);
    StringDestroy(&item);
}

void processInventory() {
    // read the item type and quantity from the input file and update the store’s inventory of the indicated item type
    String item; // Declare a String datatype = var <name>
    int quantity;
    readString(&item); // Take item -> item
    readNum(&quantity); // Read # of items -> quantity

    String Books = StringCreate("Books"); // Create a var Book to store the created "Books" string -> Use to compare
    String Dice = StringCreate("Dice");
    String Figures = StringCreate("Figures");
    String Tower = StringCreate("Towers");

    if(quantity > 0){ // *** Asked TAs about negative items ***
        if(StringIsEqualTo(&item, &Books)){
            num_books += quantity; // Updating the store inventory
        }
        else if(StringIsEqualTo(&item, &Dice)){
            num_dice += quantity; // Updating the store inventory
        }
        else if(StringIsEqualTo(&item, &Figures)){
            num_figures += quantity; // Updating the store inventory
        }
        else if(StringIsEqualTo(&item, &Tower)) {
            num_towers += quantity; // Updating the store inventory
        }
    }

    // Destroy all the string I created
    StringDestroy(&Books);
    StringDestroy(&Dice);
    StringDestroy(&Figures);
    StringDestroy(&Tower);
    StringDestroy(&item);
}

/* Personal Note:
 *
        // I don't know the name of the Customer -> have to check my Customer data -> if not -> added into the list
        // 1st Read = Craig; 2nd read = items

        Tutors names:
        - Gabriel
        - Sona
        - Nandita

        // reset


        // Process purchase:
            // If I found the customer -> update their status
            // If I not found the customer -> added them in the Data base, then update their status

        // Error orccur:
        - Because we haven't added the new customer in -> Can't use Customer[].name

 */
