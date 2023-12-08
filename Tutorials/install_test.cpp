#include "llframe/llframe.hpp"
#include <iostream>
#include <cstdint>
int main()
{
    llframe::int16_t a = 3;
    if (sizeof(a) == sizeof(std::int16_t))
        std::cout << "base type ok\n";
    return 0;
}