#include "Date.h"
#include <iostream>
#include "Customer.h"
#include <vector>
#include "Account.h"
#include <fstream>

using namespace std;

const bool findSSN(string ssn, vector <Customer> customers) { //Given vector has any elemnt with a specifiec snn or not
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].getSNN() == ssn) {
            return true;
        }
    }
    return false;
}

//Return index to customer object with given snn
int findCustomerInd(string snn, vector <Customer> :: iterator customersIterator, vector <Customer> :: iterator endIterator) {
    int ans = 0;
    for (; customersIterator != endIterator; customersIterator++, ans++) {
        if (snn == customersIterator -> getSNN()) {
            return ans;
        }
    }
    return -1;
}

int findAccountInd(string accountNumber, vector <Account> :: iterator accountsIterator, vector <Account> :: iterator endIterator) {
    int ans = 0;
    for (; accountsIterator != endIterator; accountsIterator++, ans++) {
        if (accountNumber == accountsIterator -> getNumber()) {
            return ans;
        }
    }
    return -1;
}

int main() {
    vector <Customer> customers;
    vector <Account> accounts;

    int wantedOperation;
    while (cin >> wantedOperation) {
        switch (wantedOperation) {
            case 1: { //Add costumer
                Customer newCustomer;
                //Giving input using overloaded operator from user and check for before occurence
                const bool successful = !findSSN(cin >> newCustomer, customers);
                if (successful) {
                    customers.push_back(newCustomer);
                    cout << "Client added successfully!\n";
                } else {
                    cout << "A client with the same SSN has already been registered!\n";
                }
            }
            break;

            case 10: { //Add account
                string snn, accountNumber;
                long long balance;
                cin >> snn; //Supposed that given snn is valid and registered
                int customerInd = findCustomerInd(snn, customers.begin(), customers.end());
                Customer* customer = &customers[customerInd]; //Pointer to given snn customer
                cin >> balance >> accountNumber;
                accounts.push_back(Account(snn, balance, accountNumber));
                customer -> addAccount(accountNumber);
                cout << "Account added successfully!\n";
            }
            break;

            case 2: { //Deposit
                string accountNumber;
                long long amount;
                cin >> accountNumber >> amount;
                int accountInd = findAccountInd(accountNumber, accounts.begin(), accounts.end());
                if (accountInd != -1) { //Case of found account
                    Account* account = &accounts[accountInd]; //Pointer to given account
                    account -> addToBalance(amount);
                    cout << "Deposition successful!\n";
                } else { //Case of not found acount
                    cout << "No account with this number was found!\n";
                }
            }
            break;

            case 3: { //Withdraw
                string accountNumber;
                long long amount;
                cin >> accountNumber >> amount;
                int accountInd = findAccountInd(accountNumber, accounts.begin(), accounts.end());
                if (accountInd != -1) { //Case of found account
                    Account* account = &accounts[accountInd]; //Pointer to given account
                    if (account -> getBalance() < amount) { //Case of large amount of withdrawal
                        cout << "No account with this number was found or the amount you want to withdraw is larger than your balance!\n";
                    } else { //Oh yes it was successful!
                        account -> withdraw(amount);
                        cout << "Withdrawal successful!\n";
                    }
                } else { //Case of not found acount
                    cout << "No account with this number was found or the amount you want to withdraw is larger than your balance!\n";
                }                
            }
            break;

            case 4: { //Transaction
                string departureAccountNumber, destinationAccountNumber;
                int amount;
                cin >> departureAccountNumber >> destinationAccountNumber >> amount;
                int departureAccountInd = findAccountInd(departureAccountNumber, accounts.begin(), accounts.end());
                int destinationAccountInd = findAccountInd(destinationAccountNumber, accounts.begin(), accounts.end());
                if (departureAccountInd == -1 || destinationAccountInd == -1) { //Case of not found account
                    cout << "Invalid account number(s) or the entered amount was too much!\n";
                } else {
                    Account* departureAccount = &accounts[departureAccountInd]; //Pointer to given departure account
                    Account* destinationAccount = &accounts[destinationAccountInd]; //Pointer to given destination account
                    if (departureAccount -> getBalance() < amount) { //Case of large amount of transaction
                        cout << "Invalid account number(s) or the entered amount was too much!\n";
                    } else { //Oh yes it was successful!
                        departureAccount -> withdraw(amount);
                        destinationAccount -> addToBalance(amount);
                        cout << "Transaction successful!\n";
                    }
                }
            }
            break;

            case 5: { //Change info
                string snn;
                Customer newInfo;
                cin >> snn >> newInfo;
                int customerInd = findCustomerInd(snn, customers.begin(), customers.end());
                if (customerInd == -1) {
                    cout << "Client not found!\n";
                } else {
                    Customer* customer = &customers[customerInd]; //Pointer to given snn customer
                    customer -> changeInfo(newInfo); //Change info without changing accounts 
                    cout << "You changed info!\n";
                }
            }
            break;

            case 6: { //Show info
                string snn;
                cin >> snn;
                int customerInd = findCustomerInd(snn, customers.begin(), customers.end());
                if (customerInd == -1) { //Not found
                    cout << "Client not found!\n";
                } else { //Found
                    Customer* customer = &customers[customerInd]; //Pointer to given snn customer
                    customer -> showInfo(); //Show in wanted format
                }
            }
            break;

            case 7: { //Delete account
                string snn, accountNumber;
                cin >> snn >> accountNumber;
                int customerInd = findCustomerInd(snn, customers.begin(), customers.end());
                int accountInd = findAccountInd(accountNumber, accounts.begin(), accounts.end());
                if (customerInd == -1) { //Customer not found
                    cout << "Client not found!\n";
                } else if (accountInd == -1) { //Account not found
                    cout << "Account not found!\n";
                } else { //Yes it is successful!
                    accounts.erase(accounts.begin() + accountInd);
                    Customer* customer = &customers[customerInd]; //Pointer to given snn customer
                    customer -> deleteAccount(accountNumber);
                    cout << "Account deleted successfully!\n";
                }
            }
            break;

            case 8: { //Delete customer
                string snn;
                cin >> snn;
                int customerInd = findCustomerInd(snn, customers.begin(), customers.end());
                if (customerInd == -1) { //Not found
                    cout << "Client not found!\n";
                } else { //Found
                    vector <string> toDelete = customers[customerInd].getAccounts();
                    for (int i = 0; i < toDelete.size(); i++) { //Delete all of his/her accounts
                        string cur = toDelete[i];
                        int accountInd = findAccountInd(cur, accounts.begin(), accounts.end());
                        if (accountInd != -1) {
                            accounts.erase(accounts.begin() + accountInd);
                        }
                    }
                    customers.erase(customers.begin() + customerInd); //Delete customer object
                    cout << "The client is deleted!\n";
                }
            }
            break;

            case 9: { //Write storage on files
                //File opening
                ofstream customersFile("customers.txt", ios::out);
                ofstream accountsFile("accounts.txt", ios::out);
                
                //Customer file writing
                for (int i = 0; i < customers.size(); i++) {
                    customersFile << customers[i].getSNN() << ' ' << customers[i].getName() << ' ' << customers[i].getFamily() << ' ' << 
                    customers[i].getGender() << ' ' << customers[i].getBirthday().getInfo() << endl;
                }
                customersFile.close();

                //Accounts file writing
                for (int i = 0; i < accounts.size(); i++) {
                    accountsFile << accounts[i].getNumber() << ' ' << accounts[i].getOwnerSNN() << ' ' << accounts[i].getBalance() << endl;
                }
                accountsFile.close();
            }
            break;
        }
    }
}