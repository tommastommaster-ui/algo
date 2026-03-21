#include "myClass.h"
#include <iostream>


void HashTable::addAktie(Aktie neu) {
    int index = hashCalc::intToHash(neu.name);

    int i = 0;
    while (table[(index + i * i) % TABLE_SIZE] != nullptr) {
        i++;
    }

    table[(index + i * i) % TABLE_SIZE] = new Aktie(neu);
}

Aktie* HashTable::search(const std::string& key) {
    int index = hashCalc::intToHash(key);
    int i = 0;

    while (i < TABLE_SIZE) { // maximal alle Slots prüfen
        int probe = (index + i * i) % TABLE_SIZE;
        if (table[probe] == nullptr) {
            return nullptr; // leer → nicht gefunden
        }
        if (table[probe]->name == key || table[probe]->kuerzel == key) {
            return table[probe]; // gefunden
        }
        i++;
    }
    return nullptr; // nach allen Versuchen nichts gefunden
}