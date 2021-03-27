#include "iostream"
#include <sstream>
#include <chrono>
#include "../MT.hpp"

std::string decimalToHex(u32 decimal)
{
    std::stringstream my_ss;
    my_ss << std::hex << decimal;
    std::string res = my_ss.str();  
    return res;
}

int main(void) 
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    u32 seed;
    std::cout << "Seed: 0x";
    std::cin >> std::hex >> seed;
    MT mt(seed);

    /* Getting number of milliseconds as a double. */
    auto t1 = high_resolution_clock::now();
    for (int i=0;i<100000;i++)
    {
        seed = mt.next();
        //std::cout << decimalToHex(seed) << std::endl;
    }
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count() << "ms\n";
    return 0;
}