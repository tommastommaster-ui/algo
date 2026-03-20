#ifndef MYCLASS_H
#define MYCLASS_H
#include <string>
class hashCalc
{
    private:
        static const int tableSize = 2003;

    public:
        int tableArray[tableSize];
        int intToHash(std::string aktie);
};


#endif