#pragma once

#include <iostream>
#include "utility.h"

using namespace std;

class Item {
public:
    string name;
    int count;
    int price;

    Item() {
        this->name = "";
        this->count = 0;
        this-> price = 0;
    }

    void setValues(string pName, int pCount, int pPrice) {
        this->name = pName;
        this->count = pCount;
        this->price = pPrice;
    }

};


class VendingMachineInventory {
public:

    const int DRINK_COST = 75;
    static const int INVENTORY_SIZE = 6;
    Item coke;
    Item pepsi;
    Item RC;
    Item jolt;
    Item faygo;
    Item cup;

    Item* inventory[INVENTORY_SIZE] = {&coke, &pepsi, &RC, &jolt, &faygo, &cup}; 

    VendingMachineInventory() {
        coke.setValues("Coke", 10, DRINK_COST);  // name, quantity, cost
        pepsi.setValues("Pepsi", 10, DRINK_COST);
        RC.setValues("RC", 10, DRINK_COST);
        jolt.setValues("Jolt", 10, DRINK_COST);
        faygo.setValues("Faygo", 10, DRINK_COST);
        
        // cups are free
        cup.setValues("Cups", 10, 0);
    }
    
    void printInventory() {
        for(int i = 0; i < INVENTORY_SIZE; i++){
            cout << "total " << this->inventory[i]->name << " = " 
            << this->inventory[i]->count << endl;
        }
    }

    void printCount(int itemIndex) {
        cout << "Current quantity of " << this->inventory[itemIndex]->name
        << ": "<< this->inventory[itemIndex]->count << endl; 
    }

    int findItem(string pName) { // no need to process the string (upper or lower case) before passing it
        if (stringUpper(pName) == "RC") {
            return 2;
        }
        else {
            pName = stringLower(pName);
            pName[0] = toupper(pName[0]);
            for(int i = 0; i < INVENTORY_SIZE; i++) {
                if (this->inventory[i]->name == pName) {
                    return i;
                }
            }
        }
        return -1;
    }

    // only works for the cola
    void add(string brand, int quantity) {
        if (quantity < 0) {
            cout << "Cannot add a number less than zero" << endl;
            return;
        }
        
        int itemIndex = findItem(brand);
        if (itemIndex == -1 || itemIndex == 5) {
            cout << "An invalid brand was entered" << endl;
            return;
        }
        
        this->inventory[itemIndex]->count += quantity;
        printCount(itemIndex);
        return;
    }

    // only works for the cups
    void add(int quantity) {
        if (quantity < 0) {
            cout << "Cannot add a number less than zero" << endl;
            return;
        }
        
        this->inventory[5]->count += quantity;
        printCount(5);
        return;
    
    }


    // only works for the cola
    void remove(string brand, int quantity) {
        if (quantity < 0) {
            cout << "Cannot remove a number less than zero" << endl;
            return;
        }

        int itemIndex = findItem(brand);
        if (itemIndex == -1 || itemIndex == 5) {
            cout << "An invalid brand was entered" << endl;
            return;
        }
        
        this->inventory[itemIndex]->count -= quantity;
        printCount(itemIndex);
        return;
    }

    // only works for the cups
    void remove(int quantity) {
        if (quantity < 0) {
            cout << "Cannot remove a number less than zero" << endl;
            return;
        }

        if (this->inventory[5]->count <= quantity) { this->inventory[5]->count = 0; }
        else { this->inventory[5]->count -= quantity; }
        printCount(5);
        return;
    }

};
