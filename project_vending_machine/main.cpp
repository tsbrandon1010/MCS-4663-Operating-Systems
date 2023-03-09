#include <iostream>
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
    
    * enter coin
    * enter bill
    * pick can
    DONE:
   
    * help - list commands
    * exit
    * unlock with password


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
    float value;

    Currency() {
        this->name = "";
        this->printableName = "";
        this->count = 0;
        this->value = 0;
    }
    
    void setValues(string pName, string pPrintableName , int pCount, float pValue) {
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
    float price;

    Item() {
        this->name = "";
        this->count = 0;
        this-> price = 0;
    }

    void setValues(string pName, int pCount, float pPrice) {
        this->name = pName;
        this->count = pCount;
        this->price = pPrice;
    }

};

class VendingMachineTill {
private:
    float amountDeposited = 0;
    static const int TILL_SIZE = 5;
    
    Currency fiveDollar;
    Currency dollar;
    Currency quarter;
    Currency dime;
    Currency nickel;
    Currency* tender[TILL_SIZE] = {&fiveDollar, &dollar, &quarter, &dime, &nickel};
public:

    VendingMachineTill() {
        fiveDollar.setValues("Five", "Five Dollar Bills", 2, 5.0);
        dollar.setValues("One", "One Dollar Bills", 2, 1.0);
        quarter.setValues("Quarter", "Quarters", 1, 0.25);
        dime.setValues("Dime", "Dimes", 0, 0.10);
        nickel.setValues("Nickel", "Nickels", 0, 0.05);
        this->calculateAmountDeposited();
    }

    void calculateAmountDeposited() {
        float count = 0;
        for (int i = 0; i < TILL_SIZE; i++) {
            count += tender[i]->count * tender[i]->value;
        }

        this->amountDeposited = count;
    }

    float getAmountDeposited() {
        return this->amountDeposited;
    }

    int dispenseChange(int changeNeeded) { // subtracts the proper denominations to return the change to the customer
        // subtract the largest possible denomination first

        float largestDenomination;

        largestDenomination = changeNeeded / 5;

        changeNeeded;
    }

    void updateTill(int denominationIndex, int quantity) {
        this->tender[denominationIndex]->count += quantity;
        this->calculateAmountDeposited();
    }

    void printTill() {
        this->calculateAmountDeposited();
        cout << "Amount Deposited = " << amountDeposited << endl;
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

    const float DRINK_COST = .75;
    static const int INVENTORY_SIZE = 6;
    Item coke;
    Item pepsi;
    Item RC;
    Item jolt;
    Item faygo;
    Item cup;

    Item* inventory[INVENTORY_SIZE] = {&coke, &pepsi, &RC, &jolt, &faygo, &cup}; 

    VendingMachineInventory() {
        coke.setValues("Coke", 0, DRINK_COST);
        pepsi.setValues("Pepsi", 0, DRINK_COST);
        RC.setValues("RC", 0, DRINK_COST);
        jolt.setValues("Jolt", 0, DRINK_COST);
        faygo.setValues("Faygo", 0, DRINK_COST);
        
        // cups are free
        cup.setValues("Cups", 0, 0);
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
    void add(string itemType, string brand, int quantity) {
        if (quantity < 0) {
            cout << "Cannot add a number less than zero" << endl;
            return;
        }
        
        itemType = stringLower(itemType);
        if (itemType == "cola" || itemType == "colas") {
            int itemIndex = findItem(brand);
            if (itemIndex == -1 || itemIndex == 5) {
                cout << "An invalid brand was entered" << endl;
                return;
            }
            
            this->inventory[itemIndex]->count += quantity;
            printCount(itemIndex);
            return;
        }
        else {
            cout << "An invalid item type was entered" << endl;
            return;
        }
    }

    // only works for the cups
    void add(string itemType, int quantity) {
        if (quantity < 0) {
            cout << "Cannot add a number less than zero" << endl;
            return;
        }
        
        itemType = stringLower(itemType);
        if (itemType == "cups" || itemType == "cup") {
            this->inventory[5]->count += quantity;
            printCount(5);
            return;
        }
        if (itemType == "cola") {
            cout << "You need to enter a brand" << endl;
            return;
        }
        else {
            cout << "Invalid item type entered" << endl;
            return;
        }
    }


    // only works for the cola
    void remove(string itemType, string brand, int quantity) {
        if (quantity < 0) {
            cout << "Cannot remove a number less than zero" << endl;
            return;
        }
        
        itemType = stringLower(itemType);
        if (itemType == "cola" || itemType == "colas") {
            int itemIndex = findItem(brand);
            if (itemIndex == -1 || itemIndex == 5) {
                cout << "An invalid brand was entered" << endl;
                return;
            }
            
            this->inventory[itemIndex]->count += quantity;
            printCount(itemIndex);
            return;
        }
        else {
            cout << "An invalid item type was entered" << endl;
            return;
        }
    }

    // only works for the cups
    void remove(string itemType, int quantity) {
        if (quantity < 0) {
            cout << "Cannot remove a number less than zero" << endl;
            return;
        }
        
        itemType = stringLower(itemType);
        if (itemType == "cups" || itemType == "cup") {
            
            if (this->inventory[5]->count <= quantity) { this->inventory[5]->count = 0; }
            else { this->inventory[5]->count -= quantity; }
            printCount(5);
            return;
        }
        if (itemType == "cola") {
            cout << "You need to enter a brand" << endl;
            return;
        }
        else {
            cout << "Invalid item type entered" << endl;
            return;
        }
    }

};

class VendingMachine {
private:
    const float DRINK_COST = .75;
    
    bool serviceMode = true; // true = it is in service mode
    bool runningStatus = true;
    string password = "amongus"; // hard-coded password
    float currentBalance = 0;
public:        
    
    
    VendingMachineInventory inventory;    
    VendingMachineTill till;

    void setServiceMode(bool isServiceMode) {
        this->serviceMode = isServiceMode;
    }
    bool getServiceMode() {
        return this->serviceMode;
    }
    
    void exit() {
        runningStatus = false;
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
            cout << "Incorrect password was entered" << endl;
        }
    }

    void add() { // the vending machine has to call the correct corresponding add function (from the till or the inventory)
        if (this->serviceMode != true) {
            cout << "You can only access this command from the service mode!" << endl;
            return;
        }
    } 

    // normal mode
    void coin(int value) {
        if (value == 5) {
            this->currentBalance += 0.05;
            this->till.updateTill(4, 1);
        }
        if (value == 10) {
            this->currentBalance += 0.10;
            this->till.updateTill(3, 1);
        }
        if (value == 25) {
            this->currentBalance += 0.25;
            this->till.updateTill(2, 1);
        }
        else {
            cout << "An invalid denomination entered" << endl;
        }
    }
    
    void coin(string value) {
        value = stringLower(value);
        if (value == "nickel" || value == "nickels") {
            this->currentBalance += 0.05;
            this->till.updateTill(4, 1);
        }
        if (value == "dime" || value == "dimes") {
            this->currentBalance += 0.10;
            this->till.updateTill(3, 1);
        }
        if (value == "quarter" || value == "quarters") {
            this->currentBalance += 0.25;
            this->till.updateTill(2, 1);
        }
        else {
            cout << "An invalid denomination entered" << endl;
        }
    }

    void bill(int value) {
        if (value == 1) {
            this->currentBalance += 1;
            this->till.updateTill(1, 1);
        }
        if (value == 5) {
            this->currentBalance += 5;
            this->till.updateTill(0, 1);
        }
        else {
            cout << "An invalid denomination entered" << endl;
        }
    }

    void cola(string value) { // where value is the brand of cola
        // * we have to check to make sure we have enough cans and cups before dispensing 
        // * have to make sure that there is enough money to dispense a can (if not we prompt the user to enter more)
        // * when the item is dispensed we have to deduct the item from the inventory
        // if there is leftover money it should be returned to the user
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
            // need to give the customer back their money
            return;
        } 
        if (this->currentBalance < this->DRINK_COST) { // checking to see if the customer has entered enough money
            cout << "Insufficient funds" << endl << "Current balance: " << currentBalance << endl;
            return;
        }


        this->inventory.inventory[itemIndex] -= 1; // remove the desired brand
        this->inventory.inventory[5] -= 1; // remove a cup
        this->currentBalance -= this->DRINK_COST;
        cout << this->inventory.inventory[itemIndex]->name << " dispensed!" << endl << "Dispensing change..." << endl;

        // need a function to dispense change

    }

    void unlock(string pPassword) {
        if (pPassword == this->password) {
            this->serviceMode = true;
        }
        else {
            cout << "Incorrect password was entered" << endl;
        }    
    }

};

int main() {

    VendingMachine ven;

    ven.help();
    
    ven.setServiceMode(false);
    
    ven.help();

    

    system("pause");
    return 0;
}