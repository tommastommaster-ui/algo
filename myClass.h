#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>
#include <vector>
#include "PriceEntry.h"

class hashCalc
{
private:
    static const int tableSize = 2003;

public:
    static int getTableSize();
    static int intToHash(std::string aktie, std::string kuerzel, std::string WKN);
};

class Aktie
{
public:
    std::string name;
    std::string kuerzel;
    std::string WKN;
    std::vector<PriceEntry> prices;
};

class HashTable
{
public:
    static const int TABLE_SIZE = 2003;
    Aktie* table[TABLE_SIZE] = {nullptr};

    void addAktie(Aktie neu);
    Aktie* search(const std::string& key);
    void deleteAktie(const std::string& key);
};

#endif