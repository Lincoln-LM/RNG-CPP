#include "iostream"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "../LCRNG.hpp"

std::string decimalToHex(u32 decimal)
{
    std::stringstream my_ss;
    my_ss << std::hex << decimal;
    std::string res = my_ss.str();  
    return res;
}

int main(void) 
{
    std::cout << "Seed, TSV" << "\n";
    for (u32 seed=0x0;seed<0xFFFFFFFF;seed++)
    {
        PokeRNG go(seed);
        u16 low1 = go.nextUShort();
        u16 high1 = go.nextUShort();
        u16 psv1 = (low1^high1)/8;
        go.next();
        go.next();
        go.next();
        u16 low2 = go.nextUShort();
        u16 high2 = go.nextUShort();
        u16 psv2 = (low2^high2)/8;
        go.next();
        go.next();
        go.next();
        u16 low3 = go.nextUShort();
        u16 high3 = go.nextUShort();
        u16 psv3 = (low3^high3)/8;
        if (psv1 == psv2 & psv2 == psv3) {
            std::cout << decimalToHex(seed) << ", " << psv1 << "\n";
        }
    }
    return 0;
}