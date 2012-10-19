#include "stupidemulator.hpp"

#include <iostream>

StupidEmulator::StupidEmulator()
{
}

void StupidEmulator::mouseClick(int x, int y)
{
    std::cerr << "Please click at (" << x << ", " << y << ")" << std::endl;
}
