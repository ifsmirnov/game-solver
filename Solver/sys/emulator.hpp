#ifndef EMULATOR_HPP
#define EMULATOR_HPP
#include <QPoint>
class SysEventsEmulator
{
public:
    SysEventsEmulator() { }
    virtual ~SysEventsEmulator() { }

public:
    virtual void mouseClick(int x, int y, int button) = 0;
    virtual void init() { } // an ideal Clicker needs no init
};

#endif // EMULATOR_HPP
