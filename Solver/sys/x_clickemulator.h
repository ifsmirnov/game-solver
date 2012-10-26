#ifndef X_CLICKEMULATOR_H
#define X_CLICKEMULATOR_H
#include "sys/emulator.hpp"
#include "sys/clicker.hpp"

class XClickEmulator : public SysEventsEmulator
{
public:
    ~XClickEmulator();
    void mouseClick(int x, int y);
    SysEventsEmulator* Instance();

protected:
    XClickEmulator();

private:
    XClickEmulator* instance_;
    Clicker *clicker_;
};

#endif // X_CLICKEMULATOR_H
