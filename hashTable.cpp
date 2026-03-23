#include "myClass.h"
#include <iostream>


using namespace std;

void HashTable::addAktie(Aktie neu) { // Funktion zum Hinzufügen einer Aktie zur Hash-Tabelle
    int index = hashCalc::intToHash(neu.name); // Rufe die Hash-Funktion auf, um den Index basierend auf dem Namen der Aktie zu berechnen

    int i = 0; // Quadratisches Sondieren: Wenn der berechnete Index bereits belegt ist, suche nach dem nächsten freien Slot
    while (table[(index + i * i) % TABLE_SIZE] != nullptr) { // Solange der Slot belegt ist, erhöhe i
        i++;
    }

    table[(index + i * i) % TABLE_SIZE] = new Aktie(neu); // Füge die Aktie an der gefundenen Position in der Hash-Tabelle hinzu
}

Aktie* HashTable::search(const string& key) { // Funktion zum Suchen einer Aktie in der Hash-Tabelle basierend auf einem Schlüssel (Name oder Kürzel)
    // Zuerst versuchen, als Name zu suchen
    int index = hashCalc::intToHash(key); // Berechne den Index basierend auf dem Schlüssel
    int i = 0;
    while (i < TABLE_SIZE) { // Solange innerhalb der Grenzen der Tabelle
        int probe = (index + i * i) % TABLE_SIZE; // Berechne die Position für das quadratische Sondieren
        if (table[probe] == nullptr) break; // Wenn ein leerer Slot gefunden wird, ist die Suche hier beendet
        if (table[probe]->name == key) { // Wenn der Name übereinstimmt, gebe die Aktie zurück
            return table[probe]; // Aktie gefunden
        }
        i++;
    }
    
    /// durchschnittlich O(1) im Worst Case O(n)
    //O(1) bedeutet es dauert gleich lange

    // Wenn nicht gefunden, linear nach Kürzel suchen
    for (int j = 0; j < TABLE_SIZE; j++) { // Durchsuche die gesamte Tabelle linear nach einem Eintrag mit passendem Kürzel
        if (table[j] && table[j]->kuerzel == key) { // Wenn das Kürzel übereinstimmt, gebe die Aktie zurück
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
    while (i < TABLE_SIZE) {
        int probe = (index + i * i) % TABLE_SIZE;
        if (table[probe] == nullptr) break;
        if (table[probe]->name == key) {
            delete table[probe];
            table[probe] = nullptr;
            return;
        }
        i++;
    }

    // Ansonsten nach Kürzel linear suchen und löschen
    for (int j = 0; j < TABLE_SIZE; j++) {
        if (table[j] && table[j]->kuerzel == key) {
            delete table[j];
            table[j] = nullptr;
            return;
        }
    }
}



