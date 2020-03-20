#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "Date.h"
#include <istream>
#include <vector>

using namespace std;

class Customer {
    private:
    string snn, name, family, gender;
    Date birthday;
    vector <string> accountNumbers;

    public:
    Customer(){} //Just fo ignorance of declaring empty customer object
    Customer(string name, string family, Date birthday, string gender, string snn);
    string getSNN();
    void addAccount(string accountNumber);
    void changeInfo(Customer newInfo);
    void showInfo() const;
    void deleteAccount(const string accountNumber);
    vector <string> getAccounts() const;
    const string getName() const;
    const string getFamily() const;
    const char getGender() const;
    const Date getBirthday() const;
};

const Date Customer::getBirthday() const {
    return birthday;
}

const char Customer::getGender() const {
    return (gender[0] == 'M' || gender[0] == 'm') ? 'M' : 'F';
}

const string Customer::getName() const {
    return name;
}

const string Customer::getFamily() const {
    return family;
}

vector <string> Customer::getAccounts() const {
    return accountNumbers;
}

void Customer::deleteAccount(const string accountNumber) {
    for (int i = 0; i < accountNumbers.size(); i++) {
        if (accountNumbers[i] == accountNumber) {
            accountNumbers.erase(accountNumbers.begin() + i);
            return;
        }
    }
}

void Customer::showInfo() const {
    cout << name << ' ' << family << ' ' << birthday.getInfo() << ' ' << gender << ' ' << snn << '\n';
}

void Customer::changeInfo(Customer newInfo) { //passing new Info by an customer object to the function
    //This pointer helps us to successfuly distinguish between given attributes and current object attributes
    this -> name = newInfo.name;
    this -> family = newInfo.family;
    this -> birthday = newInfo.birthday;
    this -> gender = newInfo.gender;
    this -> snn = newInfo.snn;
}

void Customer::addAccount(string accountNumber) {
    accountNumbers.push_back(accountNumber);
}

Customer::Customer(string name, string family, Date birthday, string gender, string snn) {
    //This pointer helps us to successfuly distinguish between given attributes and current object attributes
    this -> name = name;
    this -> family = family;
    this -> birthday = birthday;
    this -> gender = gender;
    this -> snn = snn;
}

string Customer::getSNN() {
    return snn;
}

string operator>>(istream& input, Customer& newCostumer) {
    string name, family, gender, snn;
    Date birthday;
    cin >> name >> family;
    cin >> birthday;
    cin >> gender >> snn;
    newCostumer = Customer(name, family, birthday, gender, snn);
    return snn;
}

#endif