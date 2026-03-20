#include "myClass.h"
#include "PriceEntry.h"
#include <iostream>
#include <string>

enum State { EMPTY, OCCUPIED, DELETED };

int main(){

    std::string name = "ABC";
    long long hash = 0;
    hashCalc hc;
    hash = hc.intToHash(name);
    std::cout << hash << std::endl;

    return 0;
}
