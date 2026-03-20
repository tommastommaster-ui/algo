#include "myClass.h"
#include <iostream>


int main(){

    std::string name = "ABC";
    long long hash = 0;
    hashCalc hc;
    hash = hc.intToHash(name);
    std::cout << hash << std::endl;

    return 0;
}
