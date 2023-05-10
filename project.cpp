/*
Project for CS 201
Author: Abia Khan
Student ID: ac6212
Date: 5/5/2023
*/


#include "project.h"

//BankAccount class implementation 
BankAccount::BankAccount()
{
    m_accountNumber = 0;
    m_balance = 0.0;
}
BankAccount::BankAccount(const float balance)  //const added 
{
    static int s_accountNumber = 0;  //static variable to keep track of account numbers
    s_accountNumber++;  //increment the static variable for each new account created
    m_accountNumber = s_accountNumber;
    m_balance = balance;
}
int BankAccount::getAccountNumber() const  //const added
{ 
    return m_accountNumber; 
} 
float BankAccount::getBalance() const  //const added
{ 
    return m_balance; 
} 
void BankAccount::deposit(float cash) 
{
    m_balance += cash; 
}
bool BankAccount::withdraw(float cash)
{
    if (m_balance < cash)
    {
        std::cout << "Withdrawal failed. Account Balance Insufficient.\n";
        return false;
    }
    else
    {
        m_balance -= cash;
        std::cout << "Withdrawal Successful.\n";
        return true;
    }
} 

//Customer class implementation
Customer::Customer(std::string name) : m_name(name) {}
std::string Customer::getName() 
{ 
    return m_name; 
}
std::vector<BankAccount *> Customer::getAccounts() 
{ 
    return m_accounts; 
}
int Customer::getNumAccounts() const  //const added 
{ 
    return m_accounts.size(); 
}
void Customer::addAccount(BankAccount &account) 
{ 
    m_accounts.push_back(&account); 
}
bool Customer::removeAccount(BankAccount account)
{
    for (auto i = 0; i < m_accounts.size(); i++) 
    {
        if (m_accounts[i]->getBalance() == account.getBalance()) 
        { 
            m_accounts.erase(m_accounts.begin() + i);            
            return true;        
        }    
    }    
    
    return false;
}

//Bank class implementation
Bank::Bank(std::string name) : m_name(name), m_NumCustomers(0) {}
std::vector<Customer *> Bank::getCustomers() 
{ 
    return m_customers; 
}
int Bank::getNumCustomers() const  //const added 
{ 
    return m_NumCustomers; 
}
void Bank::addCustomer(Customer &customer)
{
    m_customers.push_back(&customer);
    m_NumCustomers++;
}
bool Bank::removeCustomer(std::string name)
{
    for (auto i = m_customers.begin(); i != m_customers.end(); i++)
    {
        if ((*i)->getName() == name)
        {
            m_customers.erase(i);
            m_NumCustomers--;
            return true;
        }
    }
    
    return false;
}
bool Bank::transfer(BankAccount &from_account, BankAccount &to_account, float amount)
{
    if (from_account.getBalance() < amount)
    {
        std::cout << "Transfer failed. Insufficient funds.\n";
        return false;
    }
    else
    {
        from_account.withdraw(amount);
        to_account.deposit(amount);
        return true;
    }
}

int main()
{

    BankAccount account_1 = BankAccount();
    BankAccount account_2 = BankAccount(1000);
    BankAccount account_3 = BankAccount(500);
    BankAccount account_4 = BankAccount(3650);
    BankAccount account_5 = BankAccount(27553);
    BankAccount account_6 = BankAccount(100);

    Customer customer_1 = Customer("Alice");
    Customer customer_2 = Customer("Bob");

    customer_1.addAccount(account_1);
    customer_1.addAccount(account_2);

    customer_2.addAccount(account_3);
    customer_2.addAccount(account_4);
    customer_2.addAccount(account_5);

    // Check the number of account for customers
    std::cout << "Check: " << customer_1.getNumAccounts() << " = 2" << std::endl;
    std::cout << "Check: " << customer_2.getNumAccounts() << " = 3\n"
              << std::endl;

    Bank bank("ABC");

    bank.addCustomer(customer_1);
    bank.addCustomer(customer_2);

    // Check the number of customer for customers
    std::cout << "Check: " << bank.getNumCustomers() << " = 2\n"
              << std::endl;

    // Check whether the new account is added
    customer_1.addAccount(account_6);
    std::cout << "Check: " << bank.getCustomers()[0]->getNumAccounts() << " = 3\n"
              << std::endl;

    // Check whether the account is updated
    account_1.deposit(100);
    std::cout << "Check: " << bank.getCustomers()[0]->getAccounts()[0]->getBalance() << " = 100\n"
              << std::endl;

    // Check whether the withdraw is failed
    account_1.withdraw(1000);
    std::cout << "Check: " << bank.getCustomers()[0]->getAccounts()[0]->getBalance() << " = 100\n"
              << std::endl;

    // Check whether the withdraw is done
    account_1.withdraw(100);
    std::cout << "Check: " << bank.getCustomers()[0]->getAccounts()[0]->getBalance() << " = 0\n"
              << std::endl;

    // Check whether the withdraw is failed
    account_1.withdraw(100);
    std::cout << "Check: " << bank.getCustomers()[0]->getAccounts()[0]->getBalance() << " = 0\n"
              << std::endl;

    // Check whether the transfer is done
    bank.transfer(account_2, account_3, 100.0);
    std::cout << "Check: " << bank.getCustomers()[0]->getAccounts()[1]->getBalance() << " = 900" << std::endl;
    std::cout << "Check: " << bank.getCustomers()[1]->getAccounts()[0]->getBalance() << " = 600\n"
              << std::endl;

    // Check whether the transfer is failed
    bank.transfer(account_2, account_3, 1000.0);
    std::cout << "Check: " << bank.getCustomers()[0]->getAccounts()[1]->getBalance() << " = 900" << std::endl;
    std::cout << "Check: " << bank.getCustomers()[1]->getAccounts()[0]->getBalance() << " = 600\n"
              << std::endl;

    customer_1.removeAccount(account_1);
    std::cout << "Check: " << bank.getCustomers()[0]->getNumAccounts() << " = 2\n"
              << std::endl;

    bank.removeCustomer("Alicee");
    std::cout << "Check: " << bank.getNumCustomers() << " = 2\n"
              << std::endl;

    bank.removeCustomer("Alice");
    std::cout << "Check: " << bank.getNumCustomers() << " = 1\n"
              << std::endl;

    bank.removeCustomer("Bob");
    std::cout << "Check: " << bank.getNumCustomers() << " = 0\n"
              << std::endl;

    return 0;
}

