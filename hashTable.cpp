#include "myClass.h"
#include <iostream>


void HashTable::addAktie(Aktie neu) {
    int index = hashCalc::intToHash(neu.name, "", "");

    int i = 0;
    while (table[(index + i * i) % TABLE_SIZE] != nullptr) {
        i++;
    }

    table[(index + i * i) % TABLE_SIZE] = new Aktie(neu);
}

Aktie* HashTable::search(const std::string& key) {
    // Zuerst versuchen, als Name zu suchen
    int index = hashCalc::intToHash(key, "", "");
    int i = 0;
    while (i < TABLE_SIZE) {
        int probe = (index + i * i) % TABLE_SIZE;
        if (table[probe] == nullptr) break;
        if (table[probe]->name == key) {
            return table[probe];
        }
        i++;
    }

    // Wenn nicht gefunden, linear nach Kürzel suchen
    for (int j = 0; j < TABLE_SIZE; j++) {
        if (table[j] && table[j]->kuerzel == key) {
            return table[j];
        }
    }
    return nullptr;
}

