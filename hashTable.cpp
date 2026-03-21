#include "myClass.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void HashTable::addAktie(Aktie neu) {
    int index = hashCalc::intToHash(neu.name, "", "");

    int i = 0;
    while (table[(index + i * i) % TABLE_SIZE] != nullptr) {
        i++;
    }

    table[(index + i * i) % TABLE_SIZE] = new Aktie(neu);
}

Aktie* HashTable::search(const string& key) {
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

bool HashTable::saveToFile(const string& filePath) const {
    ofstream out(filePath);
    if (!out.is_open()) {
        return false;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!table[i]) {
            continue;
        }

        const Aktie* a = table[i];
        out << "A|" << a->name << "|" << a->kuerzel << "|" << a->WKN << "|" << a->prices.size() << "\n";

        for (const PriceEntry& p : a->prices) {
            out << "P|" << p.date << "|" << p.close << "|" << p.volume << "|" << p.open << "|" << p.high << "|" << p.low << "\n";
        }
    }

    return true;
}

bool HashTable::loadFromFile(const string& filePath) {
    ifstream in(filePath);
    if (!in.is_open()) {
        return false;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i]) {
            delete table[i];
            table[i] = nullptr;
        }
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        if (line.rfind("A|", 0) != 0) {
            continue;
        }

        vector<string> parts;
        string token;
        stringstream ss(line);
        while (getline(ss, token, '|')) {
            parts.push_back(token);
        }

        if (parts.size() < 5) {
            continue;
        }

        Aktie neu;
        neu.name = parts[1];
        neu.kuerzel = parts[2];
        neu.WKN = parts[3];

        int priceCount = 0;
        try {
            priceCount = stoi(parts[4]);
        } catch (...) {
            priceCount = 0;
        }

        for (int i = 0; i < priceCount; i++) {
            string pLine;
            if (!getline(in, pLine)) {
                break;
            }

            if (pLine.rfind("P|", 0) != 0) {
                break;
            }

            vector<string> pParts;
            string pToken;
            stringstream pss(pLine);
            while (getline(pss, pToken, '|')) {
                pParts.push_back(pToken);
            }

            if (pParts.size() < 7) {
                continue;
            }

            PriceEntry p;
            p.date = pParts[1];
            try {
                p.close = stod(pParts[2]);
                p.volume = stoll(pParts[3]);
                p.open = stod(pParts[4]);
                p.high = stod(pParts[5]);
                p.low = stod(pParts[6]);
            } catch (...) {
                continue;
            }

            neu.prices.push_back(p);
        }

        addAktie(neu);
    }

    return true;
}

