#include "myClass.h"
#include <iostream>

using namespace std;

int hashCalc::intToHash(string aktie) {
    int h = 0; // Initialisierung des Hash-Werts
    // Nur den Namen (aktie) hashen; kuerzel und WKN werden nicht in den Hash einbezogen
    for (char c : aktie) {
        h = (h * 31 + c) % tableSize;
    }
    return h; // Am Ende wird der berechnete Hash-Wert zurückgegeben
}

int hashCalc::getTableSize() {
    return tableSize;
}

