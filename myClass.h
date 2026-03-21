#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>
#include <vector>
#include "PriceEntry.h"

using namespace std;

class hashCalc
{
private:
    static const int tableSize = 2003;

public:
    static int getTableSize();
    static int intToHash(string aktie, string kuerzel, string WKN);
};

class Aktie
{
public:
    string name;
    string kuerzel;
    string WKN;
    vector<PriceEntry> prices;
};

class HashTable
{
public:
    static const int TABLE_SIZE = 2003;
    Aktie* table[TABLE_SIZE] = {nullptr};

    void addAktie(Aktie neu);
    Aktie* search(const string& key);
    void deleteAktie(const string& key);
    bool saveToFile(const string& filePath) const;
    bool loadFromFile(const string& filePath);
};

#endif