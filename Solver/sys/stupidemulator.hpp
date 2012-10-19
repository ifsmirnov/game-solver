#ifndef STUPIDEMULATOR_HPP
#define STUPIDEMULATOR_HPP

#include "emulator.hpp"

class StupidEmulator : public SysEventsEmulator
{
public:
    StupidEmulator();

public:
    void mouseClick(int x, int y);
};

#endif // STUPIDEMULATOR_HPP
