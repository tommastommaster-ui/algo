#include "myClass.h"
#include <iostream>
Aktie* const HashTable::DELETED = reinterpret_cast<Aktie*>(-1);

using namespace std;

void HashTable::addAktie(Aktie neu) { // Funktion zum Hinzufügen einer Aktie zur Hash-Tabelle
    int index = hashCalc::intToHash(neu.name); // Ruft inToHash auf, um den Hash Wert für die Aktie zu berechnen

    int i = 0; // Quadratisches Sondieren: Wenn der berechnete Hashwert bereits belegt ist, suche nach dem nächsten freien Platz
    while (i < tableSize && table[(index + i * i) % tableSize] != nullptr && table[(index + i * i) % tableSize] != DELETED) { // Solange der berechnete Hashwert + quadr. Berechnung nicht leer ist, wird weitergesucht, % tableSize = Hashwert ist nie außerhalb
        i++; // um 1 erhöhen
    }

    if (i < tableSize) {
        table[(index + i * i) % tableSize] = new Aktie(neu); // Aktie wird eingefügt
    }
}

Aktie* HashTable::search(const string& key) { // Funktion zum Suchen einer Aktie (mit Name oder Kürzel)
    
    int index = hashCalc::intToHash(key); // Ruft inToHash auf, und berechnet den Hashwert für die Eingabe (Wenn Kürzel eingegeben => in quadr. Schleife wird nie gefunden)
    int i = 0;
    while (i < tableSize) { // Damit Schleife nicht endlos läuft
        int probe = (index + i * i) % tableSize; // Quadratisches Sondieren: zuerst am "Startplatz" suchen, dann quadratisch weiter suchen
        if (table[probe] == nullptr) break; // Wenn ein leerer Slot gefunden wird, ist die Such hier beendet => die Aktie kann auf diesem Weg nicht gefunden werden (da sie immer am ersten freien Slot eingefügt wird)
        if(table[probe] == DELETED) { 
            i++;
            continue;
        }
        if (table[probe]->name == key) { // Aktie gefunden 
            return table[probe]; // Return um zu printen
        }
        i++;
    }
    
    // Durchschnittlich O(1) im Worst Case O(n)
    // O(1) bedeutet es dauert gleich lange

    for (int j = 0; j < tableSize; j++) { // Lineare Suche: oben nicht gefunden oder ein Kürzel eingegebenDurchsuche die gesamte Tabelle linear nach einem Eintrag mit passendem Kürzel
        if (table[j] != nullptr && table[j] != DELETED && table[j]->kuerzel == key) { // Wenn das Kürzel übereinstimmt, gebe die Aktie zurück
            return table[j]; // Aktie gefunden
        }
    }
    //lineare Durchsuchung O(n) Worst case O(n)
    //O(n) bedeutet es muss alles durchgeheb
    return nullptr;
}

void HashTable::remove(const string& key) {
    // Versuche zuerst, nach Name zu löschen (quadratisches Sondieren)
    int index = hashCalc::intToHash(key); 
    int i = 0;
    while (i < tableSize) {
        int probe = (index + i * i) % tableSize;
        if (table[probe] == nullptr) break;
        if (table[probe] == DELETED) {
            i++;
            continue;
        }
        if (table[probe]->name == key) {
            delete table[probe];
            table[probe] = DELETED;
            return;
        }
        i++;
    }

    // Ansonsten nach Kürzel linear suchen und löschen
    for (int j = 0; j < tableSize; j++) {
        if (table[j] != nullptr && table[j] != DELETED && table[j]->kuerzel == key) {
            delete table[j];
            table[j] = DELETED;
            return;
        }
    }
}