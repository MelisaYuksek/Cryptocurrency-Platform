/****************************************************************************
**                  SAKARYA UNIVERSITY
**                  FACULTY OF COMPUTER AND INFORMATION SCIENCES
**                  DEPARTMENT OF COMPUTER ENGINEERING
**                  INTRODUCTION TO PROGRAMMING COURSE
**
**                  ASSIGNMENT NUMBER……: 2
**                  STUDENT NAME................: Melisa Yüksek
**                  STUDENT ID…………………: G231210005
**                  COURSE GROUP………: C
****************************************************************************/

// Header includes
#define _CRT_SECURE_NO_WARNINGS  
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

// Constants and variables
const int MAX_ACCOUNTS = 20;
double CryptoValue = 1.0;
const char* bold = "\033[1m";
const char* italic = "\033[3m";
const char* reset = "\033[0m";

// Date class for handling date-related operations
class Date {
public:
    // Constructor to initialize with the current date
    Date() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        day = ltm->tm_mday;
        month = 1 + ltm->tm_mon;
        year = 1900 + ltm->tm_year;
    }

    // Display the current date
    void showDate() const {
        cout << day << "." << month << "." << year;
    }

    // Edit the date
    void editDate(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    // Get the current date as a tm struct
    tm currentDate() const {
        time_t now = time(0);
        return *localtime(&now);
    }

    // Calculate the difference between the current date and the stored date
    int dateDifference() const {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        return ltm->tm_mday - day;
    }

private:
    int day;
    int month;
    int year;

    friend class Account; // Private access for the Account class
};

// Function to update the global cryptocurrency value
void updateCryptoValue() {
    double randomChange = ((rand() % 21) - 10) / 100.0;
    CryptoValue *= (1.0 + randomChange);
}

// Account class for managing user accounts
class Account {
public:
    Date date;

    // Get the amount in the account
    double getAmount() const {
        return amount;
    }

    int accountNumber;

    // Constructor to initialize the account with an amount
    Account(double amount) : amount(amount), initialAmount(amount* (1.0 + 0.01)) {
        accountNo = getAccountNo();
        accountNumber = accountNo;  // Set account number to account ID
        date = Date();
    }

    // Virtual function for buying cryptocurrency
    virtual void buy(double amount) {
        double randomChange = ((rand() % 21) - 10) / 100.0;
        CryptoValue *= (1.0 + randomChange);

        double oldAmount = amount;
        amount *= GetCryptoValue(); // Update with the current crypto value
        this->amount += amount; // Update the balance

        double purchaseCost = oldAmount * (1.0 + randomChange);
        double profitLoss = amount - purchaseCost;

        cout << oldAmount << " cryptocurrency bought. Purchase cost: " << purchaseCost << endl;
    }

    // Virtual function for selling cryptocurrency
    virtual void sell(double amount) {
        if (amount > this->amount) {
            cout << "Insufficient balance!" << endl;
        }
        else {
            double randomChange = ((rand() % 21) - 10) / 100.0;
            CryptoValue *= (1.0 + randomChange);

            double oldAmount = amount;
            amount *= GetCryptoValue(); // Update with the current crypto value
            this->amount -= amount; // Update the balance

            double sellingAmount = oldAmount * (1.0 + randomChange);
            double profitLoss = amount - sellingAmount;

            cout << oldAmount << " cryptocurrency sold. Selling amount: " << sellingAmount << endl;
        }
    }

    // Display the account balance
    void balance() const {
        cout << "\nBalance: " << amount << " Coins ";
        cout << endl;
    }

    // Calculate the profit/loss
    double profit() const {
        double currentAmount = amount * GetCryptoValue();
        return currentAmount - initialAmount;
    }

    // List all accounts
    void listAccounts(Account* accounts[], int accountCount) {
        for (int i = 0; i < accountCount; ++i) {
            accounts[i]->balance();
        }
    }

    // Edit the stored date
    void editDate(int day, int month, int year) {
        date.editDate(day, month, year);
    }

    // Get a random account number
    int getAccountNo() const {
        srand(time(0));
        int ID = (rand() % 900) + 100;
        return ID;
    }

    // Virtual function to get the current cryptocurrency value
    virtual double GetCryptoValue() const {
        return CryptoValue;
    }

protected:
    double amount;

    int accountNo;

private:
    int elapsedDays;
    double initialAmount;
};

// General Account class inheriting from Account
class GeneralAccount : public Account {
public:
    GeneralAccount(double amount) : Account(amount) {}

    // Override the buy function for General Account
    void buy(double amount) override {
        Account::buy(amount);
        dailyIncrease();
        updateCryptoValue();  // Call updateCryptoValue after the transaction
    }

    // Override the sell function for General Account
    void sell(double amount) override {
        Account::sell(amount);
        monthlyDecrease();
        updateCryptoValue();  // Call updateCryptoValue after the transaction
    }

    // Override the GetCryptoValue function for General Account
    double GetCryptoValue() const override {
        // In the general account, add a daily 1% increase and an additional fixed amount
        return Account::GetCryptoValue() * (1.0 + 0.01) + 0.5;  // Daily 1% increase and an additional 0.5 unit
    }

private:
    // Helper function for daily increase
    void dailyIncrease() {
        updateCryptoValue();
    }

    // Helper function for monthly decrease
    void monthlyDecrease() {
        if (date.dateDifference() % 15 == 0) {
            // 15% decrease every 15 days
            updateCryptoValue();
            double decreaseRate = 0.05;
            CryptoValue *= (1.0 - decreaseRate);
            cout << "GeneralAccount: 15% decrease every 15 days. \n Crypto Value: " << GetCryptoValue() << " TL" << endl;
        }
    }
};

// Private Account class inheriting from Account
class PrivateAccount : public Account {
public:
    PrivateAccount(double amount) : Account(amount) {}

    // Override the buy function for Private Account
    void buy(double amount) override {
        Account::buy(amount);
        dailyIncrease();
        updateCryptoValue();  // Call updateCryptoValue after the transaction
    }

    // Override the sell function for Private Account
    void sell(double amount) override {
        Account::sell(amount);
        monthlyDecrease();
        updateCryptoValue();  // Call updateCryptoValue after the transaction
    }

    // Override the GetCryptoValue function for Private Account
    double GetCryptoValue() const override {
        // In the private account, add a daily 5% increase and an additional fixed amount
        return Account::GetCryptoValue() * (1.0 + 0.05) + 0.2;  // Daily 5% increase and an additional 0.2 unit
    }

private:
    // Helper function for daily increase
    void dailyIncrease() {
        updateCryptoValue();
    }

    // Helper function for monthly decrease
    void monthlyDecrease() {
        // In the private account, it was updated to have a 10% decrease on any day of any month
        int randomDay = rand() % 30 + 1;  // Select a random day of the month
        if (randomDay <= 3) {
            // 10% decrease on 3 random days of the month
            updateCryptoValue();
            double decreaseRate = 0.10;
            CryptoValue *= (1.0 - decreaseRate);
            cout << "PrivateAccount: 10% decrease on 3 random days of the month. \n Crypto Value: " << GetCryptoValue() << " TL" << endl;
        }
    }
};

// Function to open a new account
void openAccount(vector<Account*>& accounts, double amount, bool isGeneralAccount) {
    if (isGeneralAccount) {
        accounts.push_back(new GeneralAccount(amount));
        cout << "General account opened. Your Account Number: " << accounts.back()->accountNumber << endl;
    }
    else {
        accounts.push_back(new PrivateAccount(amount));
        cout << "Private account opened. Your Account Number: " << accounts.back()->accountNumber << endl;
    }
}

// Function to add funds to an account
void addToAccount(Account* account, double amount) {
    account->buy(amount);
}

// Function to withdraw funds from an account
void withdrawFromAccount(Account* account, double amount) {
    account->sell(amount);
}

// User menu for account interaction
void userMenu(vector<Account*>& accounts) {
    int userChoice;
    int selectedAccountIndex = accounts.size() - 1; // Default to the last added account 

    do {
        cout << "\n\t\t\033[35m--- User Menu ---\033[0m\n" << endl;
        cout << "\t1. Buy Cryptocurrency" << endl;
        cout << "\t2. Sell Cryptocurrency" << endl;
        cout << "\t3. Current Balance Status" << endl;
        cout << "\t4. Profit/Loss Status" << endl;
        cout << "\t5. Move Date Forward/Backward" << endl;
        cout << "\t6. List All Created Accounts" << endl;
        cout << "\t0. Exit" << endl;
        cout << "\t\t\t\033[35mMake your choice:\033[0m ";
        cin >> userChoice;

        switch (userChoice) {
        case 1:
            double buyAmount;
            cout << "\nCryptocurrency: " << CryptoValue << " TL";
            cout << "\nEnter the amount of cryptocurrency you want to buy: ";
            cin >> buyAmount;

            accounts[selectedAccountIndex]->buy(buyAmount);
            break;

        case 2:
            double sellAmount;
            cout << "Enter the amount of cryptocurrency you want to sell: ";
            cin >> sellAmount;
            accounts[selectedAccountIndex]->sell(sellAmount);
            break;

        case 3:
            accounts[selectedAccountIndex]->balance();
            break;

        case 4:
        {
            double profitLoss = accounts[selectedAccountIndex]->profit();
            cout << "Profit/Loss Status: " << profitLoss << " TL" << " Current Crypto Value: " << CryptoValue << " TL" << endl;
            break;
        }

        case 5:
        {
            int numberOfDays;
            cout << "How many days forward (positive) or backward (negative) do you want to move?: ";
            cin >> numberOfDays;

            Account* selectedAccount = accounts[selectedAccountIndex];
            Date& date = selectedAccount->date;

            // Store the current crypto value before changing the date
            double oldCryptoValue = CryptoValue;

            tm updatedDate = date.currentDate();  // Get the current date
            updatedDate.tm_mday += numberOfDays;  // Update the number of days

            // Check the new date with the mktime function and fix the adjustment
            time_t t = mktime(&updatedDate);
            updatedDate = *localtime(&t);

            date.editDate(updatedDate.tm_mday, updatedDate.tm_mon + 1, updatedDate.tm_year + 1900);

            // Calculate the crypto value change based on the number of days
            double dailyIncreaseRate = (CryptoValue - oldCryptoValue) / oldCryptoValue;
            CryptoValue *= pow(1.0 + dailyIncreaseRate, numberOfDays);

            cout << "New date: ";
            date.showDate();
            cout << endl;

            // Update the crypto value
            cout << "Updated Crypto Value: " << CryptoValue << " TL" << endl;

            break;
        }

        case 6:
            cout << "\n\t\t\033[31m--- All Opened Accounts ---" << reset << endl;
            for (int i = 0; i < accounts.size(); ++i) {
                cout << " Account Number: " << accounts[i]->accountNumber
                    << " - Account Type: " << (dynamic_cast<GeneralAccount*>(accounts[i]) ? "General Account" : "Private Account")
                    << " - Balance: " << accounts[i]->getAmount() << " Coins" << endl;
            }
            break;

        case 0:
            cout << italic << "Successfully logged out of the account.\n" << reset << endl;
            break;

        default:
            cout << "Invalid choice. For security reasons, logging out..." << endl;
            return;  // Exit the loop and end the program
        }

    } while (userChoice != 0);
}

// Function to draw a star line
void starLine() {
    for (int j = 0; j < 50; j++)
        cout << '*';
    cout << endl;
}

// Main function
int main() {
    setlocale(LC_ALL, "english");

    cout << bold << "\tWelcome to the Cryptocurrency Platform" << reset << endl;
    cout << "\nSystem Date: ";
    Date().showDate();
    cout << endl;

    char accountType;
    vector<Account*> accounts;  // Use vector for dynamic storage 


    do {
        cout << "Choose account type (G: General Account, P: Private Account): ";
        cin >> accountType;

        if (accountType != 'G' && accountType != 'g' && accountType != 'P' && accountType != 'p') {
            cout << italic << bold << "\033[31mInvalid account type! Please try again.\n " << reset << endl;
            continue;  // If an invalid account type is entered, start the loop again
        }

        openAccount(accounts, 0.0, accountType == 'G' || accountType == 'g'); 

        userMenu(accounts);

        char continueOption;
        cout << "Do you want to open a new account? (Yes: Y, No: N): ";
        cin >> continueOption;

        if (continueOption != 'Y' && continueOption != 'y') {
            break;  // Exit the loop if opening a new account is not desired
        }

    } while (accounts.size() < MAX_ACCOUNTS);

    // Prevent memory leaks by freeing allocated memory
    for (int i = 0; i < accounts.size(); ++i) {
        delete accounts[i];
    }

    cout << bold << "\n\t\tSuccessfully logged out of the platform" << reset << endl;

    return 0;
}
