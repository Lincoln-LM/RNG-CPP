#ifndef MT_HPP
#define MT_HPP

#include "Global.hpp"

class MT
{
public:
    explicit MT(u32 seed = 0);
    void advance(u32 advances);
    u32 next();
    u16 nextUShort();

private:
    alignas(16) u32 mt[624];
    u16 index;

    void shuffle();
};

#endif // MT_HPP