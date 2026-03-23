#ifndef MYCLASS_H
#define MYCLASS_H
#include <string>
using namespace std;

class hashCalc
{
private:
    static const int tableSize = 2003;

public:
    static int getTableSize();
    static int intToHash(string aktie);
};

class Aktie
{
public:
    string name;
    string kuerzel;
    string WKN;
};

class HashTable
{
public:
    static const int TABLE_SIZE = 2003;
    Aktie* table[TABLE_SIZE] = {nullptr};

    void addAktie(Aktie neu);
    Aktie* search(const string& key);
    void remove(const string& key);
};

#endif