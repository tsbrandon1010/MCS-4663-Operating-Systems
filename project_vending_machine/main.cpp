#include <iostream>

using namespace std;

class VendingMachineTill {
    private:
        float amountDeposited;
        int oneDollarBillCount;
        int fiveDollarBillCount;
        int nickelCount;
        int dimeCount;
        int quarterCount;
    public:
        // Getters
        float getAmountDeposited() {
            return amountDeposited;
        }
        int getOneDollarBillCount() {
            return oneDollarBillCount;
        }
        int getFiveDollarBillCount() {
            return fiveDollarBillCount;
        }
        int getNickelCount() {
            return nickelCount;
        }
        int getDimeCount() {
            return dimeCount;
        }
        int getQuarterCount() {
            return quarterCount;
        }
        // Setters
        void SetAmountDeposited(float amount) {
            this->amountDeposited = amount;
        };
        void setOneDollarBillCount(int count) {
            this->oneDollarBillCount = count;
        }
        void setFiveDollarBillCount(int count) {
            this->fiveDollarBillCount = count;
        }
        void setNickelCount(int count) {
            this->nickelCount = count;
        }
        void setDimeCount(int count) {
            this->dimeCount = count;
        }
        void setQuarterCount(int count) { 
            this->quarterCount = count;
        }
};

class VendingMachineInventory {
    private:
        int cokeCount;
        int pepsiCount;
        int RCCount;
        int joltCount;
        int faygoCount;
        int cupCount;
    public:
        // Getters
        int getCokeCount() {
            return cokeCount;
        }
        int getPepsiCount() {
            return pepsiCount;
        }
        int getRCCount() {
            return RCCount;
        }
        int getJoltCount() {
            return joltCount;
        }
        int getFaygoCount() {
            return faygoCount;
        }
        int getCupCount() {
            return cupCount;
        }
        // Setters
        void setCokeCount(int count) {
            this->cokeCount = count;
        }
        void setPepsiCount(int count) {
            this->pepsiCount = count;
        }
        void setRCCount(int count) {
            this->RCCount = count;
        }
        void setJoltCount(int count) {
            this->joltCount = count;
        }
        void setFaygoCount(int count) {
            this->faygoCount = count;
        }
        void setCupCount(int count) {
            this->cupCount = count;
        }
};

class VendingMachine {
    private:
        bool workingMode = 0; // 0 is service mode, 1 is normal mode
        const float DRINK_COST = .75;
        
};

int main() {




    system("pause");
    return 0;
}