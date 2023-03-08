#include <iostream>
#include <string>
/*

    currently working on the status functionality.
    print till is working correctly, but it has to be combined with a print function of the machine inventory (cups and cans)



    -- Service Mode
    
    TO DO:
    
    * help - list commands
    * add cans / cups
    * add / remove money
    * exit
    * lock with password

    DONE:
    
    * status - print the till, print number of cans and cups

    -- Normal Mode
    * help - list commands
    * enter coin
    * enter bill
    * pick can
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
            cout << "Cannot add a number less than zero" << endl;
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

    int findItem(string pName) {
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

    void add(string itemType, string denomination, int quantity) {
        if (quantity < 0) {
            cout << "Cannot add a number less than zero" << endl;
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

};

class VendingMachine {
private:
    bool workingMode = 0; // 0 is service mode, 1 is normal mode  

public:        
    const float DRINK_COST = .75;
    
    bool runningStatus = true;
    string password = "";


    VendingMachineInventory inventory;    
    VendingMachineTill till;

    void setWorkingMode(bool workMode) {
        this->workingMode = workMode;
    }
    bool getWorkingMode() {
        return this->workingMode;
    }
    
    void exit() {
        runningStatus = false;
    }
    
    // service mode
    void status() { // this command prints out the ammount deposited, the machine's till, and the number of pop/cups
        this->till.printTill();
        this->inventory.printInventory();
    }

    void add() {} // the vending machine has to call the correct corresponding add function (from the till or the inventory)
};

int main() {

    VendingMachineTill till;

    till.remove("bills", 5, 10);

    system("pause");
    return 0;
}