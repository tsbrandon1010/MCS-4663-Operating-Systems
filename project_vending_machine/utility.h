#pragma once

#include <iostream>

using namespace std;

string stringUpper(string aString) {
    for (int i = 0; i < aString.size(); i++) {
        aString[i] = toupper(aString[i]);
    }
    return aString;
}

string stringLower(string aString) {
    for (int i = 0; i < aString.size(); i++) {
        aString[i] = tolower(aString[i]);
    }
    return aString;
}