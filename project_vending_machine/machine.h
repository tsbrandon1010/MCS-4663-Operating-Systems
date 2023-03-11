#pragma once

#include <iostream>
#include <iomanip>

#include "till.h"
#include "inventory.h"
#include "utility.h"


using namespace std;


class VendingMachine {
private:
    const int DRINK_COST = 75;
    static const int MAX_ARGS = 4;
    bool serviceMode = false; // true = it is in service mode
    bool runningStatus = true;
    string password = "amongus"; // hard-coded password
    int currentBalance = 100;
public:        
    
    
    VendingMachineInventory inventory;    
    VendingMachineTill till;
    
    string args[MAX_ARGS] = {"", "", "", ""};

    string getCommand(string input) {
        return input.substr(0, input.find(' '));
    }


    void exit() {
        runningStatus = false;
    }
    
    void argParse(string input) {
        
        // want to clear out the arguments everytime just in case
        args[0] = ""; args[1] = ""; args[2] = ""; args[3] = "";


        input = stringLower(input);
        input.erase(0, input.find(' ') + 1);

        string temp = input;
        size_t pos = 0;
        int counter = 0;
        
        do {
            pos = temp.find(' ');
            args[counter] = temp.substr(0, pos);
            temp.erase(0, pos + 1);
            counter += 1;
            pos = temp.find(' ');
        }
        while (pos != string::npos && counter < MAX_ARGS - 1);
        args[counter] = temp;
    

    }

    void help() {
        if (this->serviceMode == true) {
            cout << endl << "Commands in Service Mode are:" << endl <<
            "Status" << endl <<
            "Add|Remove [Cola|Cups] brand <quantity>" << endl <<
            "Add|Remove [Coins|Bills] <denomination> <quantity>" << endl <<
            "Exit" << endl <<
            "Lock [password]" << endl << endl;
        }
        if (this->serviceMode == false) {
            cout << endl << "Commands in Normal Mode are:" << endl <<
            "Coin <value> where value is 5 10 25 nickel dime quarter" << endl <<
            "Bill <value> where value is 1 5 " << endl <<
            "Cola <value> where value is coke pepsi rc jolt faygo" << endl <<
            "Exit" << endl <<
            "Unlock [password]" << endl << endl;
        }
    }    

    // service mode
    void status() { // this command prints out the ammount deposited, the machine's till, and the number of pop/cups
        this->till.printTill();
        this->inventory.printInventory();
    }

    void lock(string pPassword) {
        if (pPassword == this->password) {
            this->serviceMode = false;
        }
        else {
            cout << "Incorrect password was entered" << endl << endl;
        }
    }

    void add(string input) { // the vending machine has to call the correct corresponding add function (from the till or the inventory)

        // Add|Remove [Cola|Cups] brand <quantity>
        // Add|Remove [Coins|Bills] <denomination> <quantity>
        this->argParse(input);
    
        if (args[0] == "cup" || args[0] == "cups") { // for the cups
            string sQuantity = args[1];
            
            try {
                int iQuantity = stoi(sQuantity);
                inventory.add(iQuantity);
                return;
            }
            catch (exception ex) {
                cout << "Invalid quantity entered!" << endl;
                return;
            }
            
        }
        if (args[0] == "cola" || args[0] == "colas") {
            string brand = args[1];
            string sQuantity = args[2];

            try {
                int iQuantity = stoi(sQuantity);
                inventory.add(brand, iQuantity);
                return;
            }
            catch (exception ex) {
                cout << "Invalid quantity entered!" << endl;
                return;
            }
        }

        if (args[0] == "bill" || args[0] == "bills" || args[0] == "coin" || args[0] == "coins") {
            
            string sDenomination = args[1];
            string sQuantity = args[2];
            int iQuantity = 00;
            int iDenomination = 00;

            try {
                iQuantity = stoi(sQuantity);
            }
            catch (exception ex) {
                cout << "Invalid quantity entered!" << endl;
                return;
            }
            try {
                iDenomination = stoi(sDenomination);
                till.add(args[0], iDenomination, iQuantity);
            }
            catch (exception ex) {
                till.add(args[0], sDenomination, iQuantity);
                return;
            }

        }

        else {
            cout << "Invalid use of the add command, please try again." << endl;
            return;
        } 
    } 

    void remove(string input) {
        const int MAX_ARGS = 3;
        // Add|Remove [Cola|Cups] brand <quantity>
        // Add|Remove [Coins|Bills] <denomination> <quantity>

        this->argParse(input);

    
        if (args[0] == "cup" || args[0] == "cups") { // for the cups
            string sQuantity = args[1];
            
            try {
                int iQuantity = stoi(sQuantity);
                inventory.remove(iQuantity);
                return;
            }
            catch (exception ex) {
                cout << "Invalid quantity entered!" << endl;
                return;
            }
            
        }
        if (args[0] == "cola" || args[0] == "colas") {
            string brand = args[1];
            string sQuantity = args[2];

            try {
                int iQuantity = stoi(sQuantity);
                inventory.remove(brand, iQuantity);
                return;
            }
            catch (exception ex) {
                cout << "Invalid quantity entered!" << endl;
                return;
            }
        }

        if (args[0] == "bill" || args[0] == "bills" || args[0] == "coin" || args[0] == "coins") {
            
            string sDenomination = args[1];
            string sQuantity = args[2];
            int iQuantity = 0;
            int iDenomination = 0;

            try {
                iQuantity = stoi(sQuantity);
            }
            catch (exception ex) {
                cout << "Invalid quantity entered!" << endl;
                return;
            }
            try {
                iDenomination = stoi(sDenomination);
                till.remove(args[0], iDenomination, iQuantity);
            }
            catch (exception ex) {
                till.remove(args[0], sDenomination, iQuantity);
                return;
            }

        }

        else {
            cout << "Invalid use of the remove command, please try again." << endl;
            return;
        }         
    }

    void displayBalance() {
        cout << "$" << fixed << setprecision(2) << ((long double)currentBalance  / 100) << " is currently in the machine" << endl << endl;
    }

    // normal mode
    void coin(int value) {
        if (value == 5) {
            this->currentBalance += 5;
            this->till.updateTill(4, 1);
        }
        else if (value == 10) {
            this->currentBalance += 10;
            this->till.updateTill(3, 1);
        }
        else if (value == 25) {
            this->currentBalance += 25;
            this->till.updateTill(2, 1);
        }
        else {
            cout << "An invalid denomination was entered" << endl;
        }
        displayBalance();
    }
    
    void coin(string value) {
        value = stringLower(value);
        if (value == "nickel" || value == "nickels") {
            this->currentBalance += 5;
            this->till.updateTill(4, 1);
        }
        else if (value == "dime" || value == "dimes") {
            this->currentBalance += 10;
            this->till.updateTill(3, 1);
        }
        else if (value == "quarter" || value == "quarters") {
            this->currentBalance += 25;
            this->till.updateTill(2, 1);
        }
        else {
            cout << "An invalid denomination entered" << endl;
        }
        displayBalance();
    }

    void bill(int value) {
        if (value == 1) {
            this->currentBalance += 100;
            this->till.updateTill(1, 1);
        }
        else if (value == 5) {
            this->currentBalance += 500;
            this->till.updateTill(0, 1);
        }
        else {
            cout << "An invalid denomination entered" << endl;
        }
        displayBalance();
    }

    void bill(string value) {
        value = stringLower(value);
        if (value == "one") {
            this->currentBalance += 100;
            this->till.updateTill(1, 1);
        }
        else if (value == "five") {
            this->currentBalance += 500;
            this->till.updateTill(0, 1);
        }
        else {
            cout << "An invalid denomination entered" << endl;
        }
        displayBalance();
    }

    void cola(string value) {
        int itemIndex = this->inventory.findItem(value);
        value = stringLower(value);

        if (itemIndex == -1 || value == "cups" || value == "cup") { // checking if a proper brand name was entered
            cout << "An invalid brand was entered" << endl;
            return;
        }
        if (this->inventory.inventory[itemIndex]->count == 0) { // checking if the desired brand is in stock
            cout << "This item is out of stock!" << endl;
            return;
        }
        
        if (this->inventory.inventory[5]->count == 0) { // the cups are at index 5
            cout << "We are out of cups. We are unable to fulfill your order" << endl;
            
            this->till.dispenseChange(currentBalance);
            
            return;
        } 
        if (this->currentBalance < this->DRINK_COST) { // checking to see if the customer has entered enough money
            cout << "Insufficient funds" << endl << "Current balance: " << fixed << setprecision(2) << ((long double)currentBalance  / 100) << endl;
            return;
        }

        this->inventory.inventory[itemIndex]->count -= 1; // remove the desired brand
        this->inventory.inventory[5]->count -= 1; // remove a cup
        this->currentBalance -= this->DRINK_COST;
        cout << this->inventory.inventory[itemIndex]->name << " dispensed!" << endl << endl;
        
        if (currentBalance > 0) {
            this->till.dispenseChange(currentBalance);
        }
        else {
            cout << "There was no change to dispense, have a nice day!" << endl;
        }

    }

    void unlock(string pPassword) {
        if (pPassword == this->password) {
            this->serviceMode = true;
        }
        else {
            cout << "Incorrect password was entered" << endl << endl;
        }    
    }

    void cli(string input) {
        input = stringLower(input); // this is not secure because it means that our password can only be lowercase, but that is fine for this application
        // "common" commands
        
        string command = getCommand(input);
        
        if (input == "exit") {
            this->exit();
            return;
        }
        if (input == "help") {
            this->help();
            return;
        }

        // service mode commands
        if (input == "status") {
            if (this->serviceMode == true) { this->status(); }
            else { cout << "You do not have the permissions to do this!" << endl; }
            return;
        }
        if (command == "lock") {
            if (this->serviceMode == false) {
                cout << "The machine is already locked" << endl;
                return;
            }
            this->lock(input.substr(input.find(' ') + 1, input.size()));
            return;
        }
        
        if (command == "add") {
            if (this->serviceMode == true) { this->add(input); }
            else { cout << "You do not have the permissions to do this!" << endl; }
            return;
        }

        if (command == "remove") {
            if (this->serviceMode == true) { this->remove(input); }
            else { cout << "You do not have the permissions to do this!" << endl; }
            return;
        }

        // normal mode commands
        if (command == "unlock") {
            if (this->serviceMode == true) {
                cout << "The machine is already unlocked" << endl;
                return;
            }
            this->unlock(input.substr(input.find(' ') + 1, input.size())) ;
            return;
        }

        if (command == "coin") {
            if (this->serviceMode == true) { cout << "You must be in user mode to use this command" << endl; return;}
            else {
                argParse(input);
                try { // first try with int, then try with string
                    int denomination = stoi(args[0]);
                    coin(denomination);
                }
                catch (exception ex) {
                    coin(args[0]);
                }
                return;
            }
        }

        if (command == "bill") {
            if (this->serviceMode == true) { cout << "You must be in user mode to use this command" << endl; return;}
            else {
            argParse(input);
            try {
                int denomination = stoi(args[0]);
                bill(denomination);
            }
            catch (exception ex) {
                bill(args[0]);
            }
            
            return;
            }
        }

        if (command == "cola") {
            if (this->serviceMode == true) { cout << "You must be in user mode to use this command" << endl; return;}
            else {
                argParse(input);
                cola(args[0]);
                return;
            }
        }

        else {
            cout << "That command was not recognized!" << endl << endl;
        }
    }

    void run() { // the running mode of the vending machine
        string userInput = "";
        
        while(this->runningStatus == true) {
            if (this->serviceMode == true) {
                cout << "[SERVICE MODE]>";
            }
            else {
                cout << "[NORMAL MODE]>";
            }
            getline(cin, userInput);
            this->cli(userInput);
        }
    }

};