#include "myClass.h"
#include "PriceEntry.h"
#include <iostream>
#include <string>

int hashCalc::intToHash(std::string aktie){
    int h = 0;
    for(char c : aktie)
    {
        h = (h * 31 + c) % tableSize;
    }

    return h ;

};