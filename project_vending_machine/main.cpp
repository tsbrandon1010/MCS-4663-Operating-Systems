#include <iostream>
#include <iomanip>
#include <string>
/*

    currently working on the status functionality.
    print till is working correctly, but it has to be combined with a print function of the machine inventory (cups and cans)



    -- Service Mode
    
    TO DO:
    
    ---- make the VendingMachine class invoke the respective functions ---- 
    
    DONE:
    
    * status - print the till, print number of cans and cups
    * add cans / cups
    * add / remove money
    * lock with password
    * exit
    * help - list commands

    -- Normal Mode

    DONE:
   
    * help - list commands
    * exit
    * unlock with password
    * enter bill
    * enter coin
    * pick can


*/

using namespace std;

string stringUpper(string aString) {
    for (int i = 0; i < aString.size(); i++) {
        aString[i] = toupper(aString[i]);
    }
    return aString;
}

string stringLower(string aString) {
    for (int i = 0; i < aString.size(); i++) {
        aString[i] = tolower(aString[i]);
    }
    return aString;
}

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
        cout << "Amount Deposited = " << (long double)amountDeposited / 100 << endl;
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
        << ": "<< this->tender[itemIndex]->count << endl; 
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
        
        this->inventory[itemIndex]->count += quantity;
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

class VendingMachine {
private:
    const int DRINK_COST = 75;
    static const int MAX_ARGS = 3;
    bool serviceMode = false; // true = it is in service mode
    bool runningStatus = true;
    string password = "amongus"; // hard-coded password
    int currentBalance = 100;
public:        
    
    
    VendingMachineInventory inventory;    
    VendingMachineTill till;
    
    string args[MAX_ARGS] = {"", "", ""};

    string getCommand(string input) {
        return input.substr(0, input.find(' '));
    }


    void exit() {
        runningStatus = false;
    }
    
    void argParse(string input) {
        
        // want to clear out the arguments everytime just in case
        args[0] = ""; args[1] = ""; args[2] = "";


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
        while (pos != string::npos);
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
            cout << "Insufficient funds" << endl << "Current balance: " << currentBalance << endl;
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

int main() {


    VendingMachine ven;

    ven.run();
    

    system("pause");
    return 0;
}