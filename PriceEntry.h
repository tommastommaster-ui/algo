#ifndef PRICE_ENTRY_H
#define PRICE_ENTRY_H

#include <string>
using namespace std;

class PriceEntry {
    public:
        string date;
        double close;
        long long volume;
        double open;
        double high;
        double low;
};

#endif