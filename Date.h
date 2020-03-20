#ifndef DATE_H
#define DATE_H

#include <istream>
#include <string>
#include "StringUtility.h"

using namespace std;

class Date {
    private:
    int year, month, date;
    string originalInputForm;

    public:
    Date(int* given); //The only argumant is array of integers year, month, day
    Date(){} //Just fo ignorance of declaring empty date object

    const string getInfo() const;

    void storeOriginalInput(const string given);
};

void Date::storeOriginalInput(const string given) {
    originalInputForm = given;
}

const string Date::getInfo() const {
    return originalInputForm;
}

Date::Date(int* given) {
    year = given[0];
    month = given[1];
    date = given[2];
}

istream& operator>>(istream& input, Date& storage) {
    string s; //Given str
    input >> s;

    string splitted[3]; //We will store year, month and date separately here
    for (int i = 0, j = 0; i < s.size(); i++) {
        if (s[i] == '.') { //Case of when we wanted to increase splitted array index
            j++;
        } else { //Case of digits
            splitted[j] += s[i];
        }
    }

    int splittedInt[3]; //Storage after converting splitted strings to integer numbers
    for (int i = 0; i < 3; i++) {
        splittedInt[i] = StringUtility::convertStringToNumber(splitted[i]);
    }

    storage = Date(splittedInt); //Finally modifing given birthday object to given input from user
    storage.storeOriginalInput(s); //Later when we want to show birthday we can use original input from user

    return input; //return input in case of wanted cascade using of operator
}

#endif