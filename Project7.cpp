// CRM in C++ Project7.cpp
// EE 312 Project 7 submission by
// Teyo Turrubiates
// ttt2443
// Slip days used: 0
// Summer 2022
#include <stdio.h>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>
void readString(UTString&);
void readNum(int&);
using namespace std;
CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(UTString word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
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
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
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
    UTString input;
    UTString input1;
    int num;
    readString(input); //name
    readString(input1); //type
    readNum(num);
    //variable declarations done
    int numAvailable = *selectInventItem(input1);
    if(numAvailable < num){ //checks to see if there is enough of item requested to be bought
        cout << "Sorry " << input.c_str() << ", we only have " << numAvailable << " " << input1.c_str() << endl;
        return;
    }
    else if(num == 0){ //if customer wants 0 of type, return 0 with no message
        return;
    }
    else {
        if(input1 == "Bottles"){
            database[input].bottles += num; //[] operator should add customer if he/she does not already exist
            num_bottles -= num;
        }
        else if(input1 == "Diapers"){
            database[input].diapers += num;
            num_diapers -= num;
        }
        else{
            database[input].rattles += num;
            num_rattles -= num;
        }

    }



}

void processSummarize() {
    Customer* CustBot = findMax("Bottles");
    Customer* CustDip = findMax("Diapers");
    Customer* CustRat = findMax("Rattles");
    cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory" << endl;
    cout << "we have had a total of " << database.size() << " different customers" << endl;
    if(CustBot){
        cout << CustBot->name.c_str() << " has Purchased the most Bottles (" << CustBot->bottles << ")" << endl;
    }
    else {
        cout << "no one has purchased any Bottles" << endl;
    }
    if(CustDip){cout << CustDip->name.c_str() << " has Purchased the most Diapers (" << CustDip->diapers << ")" << endl;
    }
    else {cout << "no one has purchased any Diapers" << endl;}

    if(CustRat){cout << CustRat->name.c_str() << " has Purchased the most Rattles (" << CustRat->rattles << ")" << endl;
    }
    else {cout << "no one has purchased any Rattles" << endl;}


}

void processInventory() {
    UTString input2;
    int num;
    readString(input2);
    readNum(num);
    if(input2 == "Bottles"){
        num_bottles += num;
    }
    else if(input2 == "Diapers"){
        num_diapers += num;
    }
    else {
        num_rattles += num;
    }
}
