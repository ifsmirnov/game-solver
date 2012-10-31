#ifndef X_CLICKEMULATOR_H
#define X_CLICKEMULATOR_H
#include "sys/emulator.hpp"
#include "sys/clicker.hpp"
#include <QPoint>

class XClickEmulator : public SysEventsEmulator
{
private:
    static bool instance_flag_;
    static XClickEmulator *instance_;
    Clicker *clicker_;
    XClickEmulator()
    {
        clicker_ = new Clicker();
    }

public:
    static XClickEmulator* get_instance();

    void mouseClick(int x, int y);

    ~XClickEmulator();
};

#endif // X_CLICKEMULATOR_H
