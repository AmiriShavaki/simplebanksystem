#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Customer.h"
#include <string>

using namespace std;

class Account {
    private:
    long long balance;
    string ownerSNN; //index to owner of this account
    string accountNumber;

    public:
    Account(){}; //Just fo ignorance of declaring empty account object
    Account(string ownerSNN, long long balance, string accountNumber);
    void addToBalance(int amount);
    const string getNumber() const;
    const long long getBalance() const;
    void withdraw(long long amount);
    const string getOwnerSNN() const;
};

const string Account::getOwnerSNN() const {
    return ownerSNN;
}

void Account::withdraw(long long amount) {
    balance -= amount;
}

const long long Account::getBalance() const {
    return balance;
}

const string Account::getNumber() const {
    return accountNumber;
}

void Account::addToBalance(int amount) {
    balance += amount;
}

Account::Account(string ownerSNN, long long balance, string accountNumber) {
    //This pointer helps us to successfuly distinguish between given attributes and current object attributes
    this -> ownerSNN = ownerSNN;
    this -> balance = balance;
    this -> accountNumber = accountNumber;
}

#endif