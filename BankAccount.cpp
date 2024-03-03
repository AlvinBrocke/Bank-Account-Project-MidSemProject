/* Alvin Brocke - 69382025*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Bank Account Class
class BankAccount
{
protected:
    string accountHolderName, accountNumber;
    double balance;

public:
    // Default constructor
    // Default constructor
    BankAccount() : accountHolderName(""), accountNumber(""), balance(0.0) {}

    // Parameterized constructor
    BankAccount(const string &accountHolderName, const string &accountNumber, double balance)
        : accountHolderName(accountHolderName), accountNumber(accountNumber), balance(balance) {}

    // Copy constructor
    BankAccount(const BankAccount &bankaccount)
        : accountHolderName(bankaccount.accountHolderName), accountNumber(bankaccount.accountNumber), balance(bankaccount.balance) {}

    // Virtual function to deposit money
    virtual void deposit(double amount)
    {
        this->balance += amount;
    }

    // Virtual function to withdraw money
    virtual void withdraw(double amount)
    {
        if (amount <= balance)
        {
            this->balance -= amount;
        }
        else
        {
            cout << "\nInsufficient balance!" << endl;
        }
    }

    // Virtual function to display account information
    virtual void display() const
    {
        cout << "\nAccount Holder Name: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: Ghc." << balance << endl;
    }

    // Operator Overloading
    friend BankAccount operator+(const BankAccount &acc1, const BankAccount &acc2);
};

BankAccount operator+(const BankAccount &acc1, const BankAccount &acc2)
{
    string newName = acc1.accountHolderName + " & " + acc2.accountHolderName;
    string newNumber = acc1.accountNumber + " & " + acc2.accountNumber;
    double newBalance = acc1.balance + acc2.balance;
    return BankAccount(newName, newNumber, newBalance);
}

// Savings Account Class
class SavingsAccount : public BankAccount
{
private:
    double interestRate;

public:
    // Default constructor
    SavingsAccount() : interestRate(2.5) {} // Default interest rate of 2.5%

    // Parameterized constructor
    SavingsAccount(const string &name, const string &accNumber, double bal, double rate)
        : BankAccount(name, accNumber, bal), interestRate(rate) {}

    // Function to calculate interest
    void addInterest()
    {
        double interest = this->balance * (interestRate / 100);
        deposit(interest);
    }
};

// Checking Account Class
class CheckingAccount : public BankAccount
{
private:
    double overdraftLimit;

public:
    // Default constructor
    CheckingAccount() : overdraftLimit(1000) {} // Default overdraft limit of Ghc.1000
    // Parameterized constructor
    CheckingAccount(string name, string accNumber, double bal, double overdraft)
        : BankAccount(name, accNumber, bal), overdraftLimit(overdraft) {}

    // Overridden withdraw method
    void withdraw(double amount)
    {
        if (amount <= balance + overdraftLimit)
            balance -= amount;
        else
            cout << "\nExceeds overdraft limit!" << endl;
    }
};

// Main function
int main()
{
    // A Bank vector to store the BankAccount pointers
    vector<BankAccount *> bank;

    // Create (5) BankAccount objects and add them to the vector
    SavingsAccount *acc1 = new SavingsAccount("Alvin Brocke", "4421284943", 12500.0, 4.5);
    BankAccount *acc2 = new BankAccount("Noble Ampratwum", "475731941", 10300.0);
    BankAccount *acc3 = new BankAccount("Doreen Nkpogoh", "43578453", 8450.0);
    SavingsAccount *acc4 = new SavingsAccount("Charles Dwight", "411276590", 11870.0, 2.5);
    CheckingAccount *acc5 = new CheckingAccount("Megan King", "498744624", 13320.0, 500.0);

    // Adding the Bank accounts to the vector
    bank.push_back(acc1);
    bank.push_back(acc2);
    bank.push_back(acc3);
    bank.push_back(acc4);
    bank.push_back(acc5);

    // Display all bank in the vector
    cout << "\nAll Bank Accounts:" << endl;
    for (const BankAccount *account : bank)
    {
        account->display();
        cout << endl;
    }

    // Testing class methods
    acc1->deposit(500);
    acc1->addInterest();

    acc4->addInterest();
    acc4->withdraw(1500);

    acc3->withdraw(500);
    acc3->deposit(1000);

    acc5->withdraw(150);
    acc5->withdraw(1500);

    acc2->deposit(2000);

    // Testing operator overloading
    BankAccount acc6 = (*acc1) + (*acc2);
    bank.push_back(&acc6);

    // Display all bank accounts after methods applied
    cout << "\nAll Bank Accounts (Processed):" << endl;
    for (const auto &account : bank)
    {
        account->display();
        cout << endl;
    }

    return 0;
}
