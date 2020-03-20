#ifndef STRINGUTILITY_H
#define STRINGUTILITY_H

#include <string>

using namespace std;

class StringUtility {
    public:

    //Change type of given string to integer
    static int convertStringToNumber(string s);
};

int StringUtility::convertStringToNumber(string s) {
    int n = s.size(), ans = 0;
    for (int i = n - 1, j = 1; i >= 0; i--, j *= 10) {
        ans += (s[i] - '0') * j;
    }
    return ans;
}

#endif