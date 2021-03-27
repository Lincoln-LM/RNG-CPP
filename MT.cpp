#include "MT.hpp"

MT::MT(u32 seed) : index(624)
{
    mt[0] = seed;

    for (u32 i = 1; i < 624; i++)
    {
        seed = 0x6c078965 * (seed ^ (seed >> 30)) + i;
        mt[i] = seed;
    }
}

void MT::advance(u32 advances)
{
    advances += index;
    while (advances >= 624)
    {
        shuffle();
        advances -= 624;
    }
    index = advances;
}

u32 MT::next()
{
    if (index == 624)
    {
        shuffle();
        index = 0;
    }

    u32 y = mt[index++];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680;
    y ^= (y << 15) & 0xefc60000;
    y ^= (y >> 18);

    return y;
}

u16 MT::nextUShort()
{
    return next() >> 16;
}

void MT::shuffle()
{
    for (int i = 0; i < 624; i++) 
    {
        u32 y = ((mt[i]&0x80000000) | (mt[(i+1)%624]&0x7fffffff));
        u32 y1 = y>>1;
        if (y%2 == 1) 
        {
            y1 ^= 0x9908b0df;
        }
        mt[i] = mt[(i+397)%624]^y1;
    }
}