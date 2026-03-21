#include "myClass.h"
#include <iostream>

using namespace std;

int hashCalc::intToHash(string aktie, string kuerzel, string WKN) {
    int h = 0;
    for (char c : aktie) {
        h = (h * 31 + c) % tableSize;
    }
    for (char c : kuerzel) {
        h = (h * 31 + c) % tableSize;
    }
    for (char c : WKN) {
        h = (h * 31 + c) % tableSize;
    }
    return h;
}

int hashCalc::getTableSize() {
    return tableSize;
}