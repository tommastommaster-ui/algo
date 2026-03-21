#include "myClass.h"
#include <iostream>

int hashCalc::intToHash(std::string aktie, std::string kuerzel, std::string WKN) {
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