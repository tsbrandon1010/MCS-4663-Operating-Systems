#include <iostream>
#include <string>
/*

    currently working on the status functionality.
    print till is working correctly, but it has to be combined with a print function of the machine inventory (cups and cans)



    -- Service Mode
    * help
    * status
    * add cans / cups
    * add / remove money
    * exit
    * lock with password

    -- Normal Mode
    * help
    * enter coin
    * enter bill
    * pick can
    * exit
    * unlock with password

*/

using namespace std;

class Currency {
public:
    string name;
    int count;
    float value;

//public:
    //void setCount{}
    Currency() {
        this->name = "";
        this->count = 0;
        this->value = 0;
    }
    
    void setValues(string pName, int pCount, float pValue) {
        this->name = pName;
        this->count = pCount;
        this->value = pValue;
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
        fiveDollar.setValues("Five Dollar Bills", 2, 5.0);
        dollar.setValues("One Dollar Bills", 2, 1.0);
        quarter.setValues("Quarters", 1, 0.25);
        dime.setValues("Dimes", 0, 0.10);
        nickel.setValues("Nickels", 0, 0.05);
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
            cout << "total " << tender[i]->name << " = " << tender[i]->count << endl;
        }
    }

    
};

class VendingMachine {
private:
    bool workingMode = 0; // 0 is service mode, 1 is normal mode  

public:        
    const float DRINK_COST = .75;
    
    int cokeCount;
    int pepsiCount;
    int RCCount;
    int joltCount;
    int faygoCount;
    int cupCount;
    int* machineCount[6] = {&cokeCount, &pepsiCount, &RCCount, &joltCount, &faygoCount, &cupCount}; 
    
    VendingMachineTill till;

    bool runningStatus = true;
    string password = "";
    
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

    }
};

int main() {

    VendingMachineTill myTill;

    myTill.printTill();

    system("pause");
    return 0;
}