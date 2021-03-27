#ifndef RNGLIST_HPP
#define RNGLIST_HPP

#include "Global.hpp"

template <typename IntegerType, typename RNGType, u32 size>
class RNGList
{
public:
    explicit RNGList(RNGType &rng) : rng(rng), head(0), pointer(0)
    {
        static_assert(size && ((size & (size - 1)) == 0), "Number is not a perfect multiple of two");

        for (u32 i = 0; i < size; i++)
        {
            list[i] = this->rng.next();
        }
    }

    RNGList(const RNGList &) = delete;

    void operator=(const RNGList &) = delete;

    void advanceStates(u32 frames)
    {
        for (u32 frame = 0; frame < frames; frame++)
        {
            advanceState();
        }
    }

    void advanceState()
    {
        head &= size - 1;
        list[head++] = rng.next();

        pointer = head;
    }

    void advanceFrames(u32 frames)
    {
        pointer = (pointer + frames) & (size - 1);
    }

    IntegerType getValue()
    {
        pointer &= size - 1;
        return list[pointer++];
    }

    IntegerType getRand(u32 n)
    {
        return (getValue()*n>>32);
    }

    void resetState()
    {
        pointer = head;
    }

private:
    RNGType rng;
    IntegerType list[size];
    u32 head, pointer;
};

#endif // RNGLIST_HPP