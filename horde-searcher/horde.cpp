#include "iostream"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "../MT.hpp"
#include "../RNGList.hpp"

std::string decimalToHex(u32 decimal)
{
    std::stringstream my_ss;
    my_ss << std::hex << decimal;
    std::string res = my_ss.str();  
    return res;
}

int main(void) 
{
    for (u32 seed=0x0;seed<0xFFFFFFFF;seed++)
    {
        MT mt(seed);
        RNGList<u32, MT, 131072> rngList(mt);

        for (u32 advance=0;advance<=100000;advance++)
        {
            rngList.advanceFrames(60);
            u16 PSVs[5] = {4097,4097,4097,4097,4097};
            for (u8 slot=0;slot<5;slot++)
            {
                rngList.getValue();
                u32 EC = rngList.getValue();
                u32 PID = rngList.getValue();
                u16 PIDhigh = PID>>16;
                u16 PIDlow = PID&0xFFFF;
                u16 PSV = (PIDhigh^PIDlow)/16;
                
                /*
                u32 IVs[6] = {0,0,0,0,0,0};
                for (u8 iv=0;iv<6;iv++)
                {
                    if (IVs[iv] == 0)
                    {
                        IVs[iv] = rngList.getValue() >> 27;
                    }
                }
                */
                //std::cout << decimalToHex(seed) << std::endl;
                u16 found = std::count(std::begin(PSVs), std::end(PSVs), PSV);
                if (found+1 >= 3) {
                    std::ofstream myfile;
                    myfile.open("hordes.out", std::ios::app);
                    myfile << found+1 << " " << PSV << " " << decimalToHex(seed) << " " << advance << " " << decimalToHex(EC) << " " << decimalToHex(PID) << std::endl;
                    myfile.close();
                    std::cout << found+1 << " " << PSV << " " << decimalToHex(seed) << " " << advance << " " << decimalToHex(EC) << " " << decimalToHex(PID) << std::endl;
                }
                PSVs[slot] = PSV;
                rngList.getValue();
                rngList.getValue();
            }
            rngList.advanceState();
        }
    }
    return 0;
}