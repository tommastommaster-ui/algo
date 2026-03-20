#include <string>
#include <vector>
#include "PriceEntry.h"
using namespace std;

class Aktie {
    string name;
    string wkn;
    string symbol;
    vector<PriceEntry> prices;
};