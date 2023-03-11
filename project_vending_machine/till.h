#pragma once

#include <iostream>
#include "utility.h"
using namespace std;

class Currency {
public:
    string name;
    string printableName;
    int count;
    int value;

    Currency() {
        this->name = "";
        this->printableName = "";
        this->count = 0;
        this->value = 0;
    }
    
    void setValues(string pName, string pPrintableName , int pCount, int pValue) {
        this->name = pName;
        this->printableName = pPrintableName;
        this->count = pCount;
        this->value = pValue;
    }
    
};

class VendingMachineTill {
private:
    int amountDeposited = 0;
    static const int TILL_SIZE = 5;
    
    Currency fiveDollar;
    Currency dollar;
    Currency quarter;
    Currency dime;
    Currency nickel;
    Currency* tender[TILL_SIZE] = {&fiveDollar, &dollar, &quarter, &dime, &nickel};
public:

    VendingMachineTill() {
        fiveDollar.setValues("Five", "Five Dollar Bills", 10, 500);
        dollar.setValues("One", "One Dollar Bills", 10, 100);
        quarter.setValues("Quarter", "Quarters", 10, 25);
        dime.setValues("Dime", "Dimes", 10, 10);
        nickel.setValues("Nickel", "Nickels", 10, 5);
        this->calculateAmountDeposited();
    }

    void calculateAmountDeposited() {
        int count = 0;
        for (int i = 0; i < TILL_SIZE; i++) {
            count += tender[i]->count * tender[i]->value;
        }

        this->amountDeposited = count;
    }

    int getAmountDeposited() {
        return this->amountDeposited;
    }

    void dispenseChange(int &changeNeeded) { // subtracts the proper denominations to return the change to the customer
        // subtract the largest possible denomination first
        int largestDenomination;
        int numDispensed;
        int totalDispensed = 0;
        // we need to ensure that there are enough of each coins/bills 


        largestDenomination = changeNeeded / 500; // 5 dollar bill
        if (largestDenomination > this->tender[0]->count) { // if we dont have enough, we take that max that we possibly can and pass it to the next denomination
            numDispensed = this->tender[0]->count;
            this->tender[0]->count = 0; 
            changeNeeded -= numDispensed * 500;
        }
        else {
            numDispensed = largestDenomination;
            this->tender[0]->count -= largestDenomination;
            changeNeeded -= largestDenomination * 500;
        }
        totalDispensed += numDispensed * 500;
        cout << "Fives: " << numDispensed << endl;
        
        largestDenomination = changeNeeded / 100; // 1 dollar bill
        if (largestDenomination > this->tender[1]->count) { // if we dont have enough, we take that max that we possibly can and pass it to the next denomination
            numDispensed = this->tender[1]->count;
            this->tender[1]->count = 0; 
            changeNeeded -= numDispensed * 100;
        }
        else {
            numDispensed = largestDenomination;
            this->tender[1]->count -= largestDenomination;
            changeNeeded -= largestDenomination * 100;
        }
        totalDispensed += numDispensed * 100;
        cout << "Ones: " << numDispensed << endl;

        largestDenomination = changeNeeded / 25; // 25 cent coin
        if (largestDenomination > this->tender[2]->count) { // if we dont have enough, we take that max that we possibly can and pass it to the next denomination
            numDispensed = this->tender[2]->count;
            this->tender[2]->count = 0; 
            changeNeeded -= numDispensed * 25;
        }
        else {
            numDispensed = largestDenomination;
            this->tender[2]->count -= largestDenomination;
            changeNeeded -= largestDenomination * 25;
        }
        totalDispensed += numDispensed * 25;
        cout << "Quarters: " << numDispensed << endl;

        largestDenomination = changeNeeded / 10; // 10 cent coin
        if (largestDenomination > this->tender[3]->count) { // if we dont have enough, we take that max that we possibly can and pass it to the next denomination
            numDispensed = this->tender[3]->count;
            this->tender[3]->count = 0; 
            changeNeeded -= numDispensed * 10;
        }
        else {
            numDispensed = largestDenomination;
            this->tender[3]->count -= largestDenomination;
            changeNeeded -= largestDenomination * 10;
        }
        totalDispensed += numDispensed * 10;
        cout << "Dimes: " << numDispensed << endl;

        largestDenomination = changeNeeded / 5; // 5 cent coin
        if (largestDenomination > this->tender[4]->count) { // if we dont have enough, we take that max that we possibly can and pass it to the next denomination
            numDispensed = this->tender[4]->count;
            this->tender[4]->count = 0; 
            changeNeeded -= numDispensed * 5;
        }
        else {
            numDispensed = largestDenomination;
            this->tender[4]->count -= largestDenomination;
            changeNeeded -= largestDenomination * 5;
        }
        totalDispensed += numDispensed * 5;
        cout << "Nickels: " << numDispensed << endl;
    
        cout << "$"<< (long double)totalDispensed / 100 << " was dispensed." << endl << endl;

        if (changeNeeded != 0) { // then we did not have enough money in the machine to make change
            cout << "The vending machine is unable to return all change, please contact an attendent." << endl;
            cout << "$" << (long double) changeNeeded  / 100 << " remains in the machine." << endl;
        }

    }

    void updateTill(int denominationIndex, int quantity) {
        this->tender[denominationIndex]->count += quantity;
        this->calculateAmountDeposited();
    }

    void printTill() {
        this->calculateAmountDeposited();
        cout << "Amount Deposited = " << fixed << setprecision(2) << ((long double)amountDeposited  / 100) << endl;
        for (int i = 0; i < 5; i++) {
            cout << "total " << this->tender[i]->printableName << " = " << 
            tender[i]->count << endl;
        }
    }

    int findItem(string pName) { // returns the index of an item's name
        
        pName = stringLower(pName);
        pName[0] = toupper(pName[0]);

        for (int i = 0; i < TILL_SIZE; i++) {
            if (this->tender[i]->name == pName) {
                return i;
            }
        }

        return -1;
    }

    void printCount(int itemIndex) {
        cout << "Current quantity of " << this->tender[itemIndex]->printableName
        << ": "<< this->tender[itemIndex]->count << endl << endl; 
    }

    void add(string itemType, string denomination, int quantity) {
        if (quantity < 0) {
            cout << "Cannot add a number less than zero" << endl;
            return;
        }
        
        itemType = stringLower(itemType);
        if (itemType == "coins" || itemType == "coin" || itemType == "bills" || itemType == "bill") {
            int itemIndex = findItem(denomination);
            
            if (itemIndex == -1) {
                cout << "Invalid denomination was entered" << endl;
                return;
            }
            
            else {
                this->tender[itemIndex]->count += quantity;
                printCount(itemIndex);
                return;
            }
        }
        
        else {
            cout << "The type [Coins|Bills] was not correct" << endl;
            return;
        }
    }

    void add(string itemType, int denomination, int quantity) {
        if (quantity < 0) {
            cout << "Cannot add a number less than zero" << endl;
            return;
        }
        
        // the breaks in this switch statement are probably redundent

        itemType = stringLower(itemType);
        if (itemType == "coins" || itemType == "coin") {
            
            switch (denomination)
            {
            case 5:
                this->tender[4]->count += quantity;
                printCount(4);
                return;
                break;
            case 10:
                this->tender[3]->count += quantity;
                printCount(3);
                return;
                break;
            case 25:
                this->tender[2]->count += quantity;
                printCount(2);
                return;
                break; 
            default:
                cout << "An invalid denomination was entered" << endl;
                return;
                break;
            }
        }
        
        if (itemType == "bills" || itemType == "bill") {
            switch (denomination)
            {
                case 5:
                    this->tender[0]->count += quantity;
                    printCount(0);
                    return;
                    break;
                case 1:
                    this->tender[1]->count += quantity;
                    printCount(1);
                    return;
                    break;
                default:
                    cout << "An invalid denomination was entered" << endl;
                    return;
                    break;
            }
        }

        else {
            cout << "The type [Coins|Bills] was not correct" << endl;
            return;
        }
    }

    void remove(string itemType, string denomination, int quantity) {
        if (quantity < 0) {
            cout << "Cannot remove a number less than zero" << endl;
            return;
        }
        
        itemType = stringLower(itemType);
        if (itemType == "coins" || itemType == "coin" || itemType == "bills" || itemType == "bill") {
            int itemIndex = findItem(denomination);
            
            if (itemIndex == -1) {
                cout << "Invalid denomination was entered" << endl;
                return;
            }
            else {
                
                if (this->tender[itemIndex]->count <= quantity) { this->tender[itemIndex]->count = 0; } 
                else { this->tender[itemIndex]->count -= quantity; }
                printCount(itemIndex);
                return;
            }
        }
        else {
            cout << "The type [Coins|Bills] was not correct" << endl;
            return;
        }
    }

    void remove(string itemType, int denomination, int quantity) {
        if (quantity < 0) {
            cout << "Cannot remove a number less than zero" << endl;
            return;
        }
        
        itemType = stringLower(itemType);
        if (itemType == "coins" || itemType == "coin") {
            
            if (denomination == 5) {
                if (this->tender[4]->count <= quantity) { this->tender[4]->count = 0; }
                else { this->tender[4]->count -= quantity; }
                printCount(4);
                return;
            }
            if (denomination == 10) {
                if (this->tender[3]->count <= quantity) { this->tender[3]->count = 0; }
                else { this->tender[3]->count -= quantity; }
                printCount(3);
                return;
            }
            if (denomination == 25) {
                if (this->tender[2]->count <= quantity) { this->tender[2]->count = 0; }
                else { this->tender[2]->count -= quantity; }
                printCount(2);
                return;
            }
            else {
                cout << "An invalid denomination was entered" << endl;
                return;
            }
        }
        
        if (itemType == "bills" || itemType == "bill") {
            
            if (denomination == 5) {
                if (this->tender[0]->count <= quantity) { this->tender[0]->count = 0; }
                else { this->tender[0]->count -= quantity; }
                printCount(0);
                return;
            }
            if (denomination == 1) {
                if (this->tender[1]->count <= quantity) { this->tender[1]->count = 0; }
                else { this->tender[1]->count -= quantity; }
                printCount(1);
                return;
            }
            else {
                cout << "An invalid denomination was entered" << endl;
                return;
            }
        }

        else {
            cout << "The type [Coins|Bills] was not correct" << endl;
            return;
        }
    }    

};