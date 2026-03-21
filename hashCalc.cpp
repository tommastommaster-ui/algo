#include "myClass.h"
#include <iostream>

int hashCalc::intToHash(std::string aktie) {
    int h = 0;
    for (char c : aktie) {
        h = (h * 31 + c) % tableSize;
    }
    return h;
}

int hashCalc::getTableSize() {
    return tableSize;
}