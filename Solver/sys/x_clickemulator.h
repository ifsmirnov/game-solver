#ifndef X_CLICKEMULATOR_H
#define X_CLICKEMULATOR_H
#include "sys/emulator.hpp"
#include "sys/clicker.hpp"
#include <QPoint>
#include <memory>

class XClickEmulator : public SysEventsEmulator
{
private:
    static bool instance_flag_;
    static std::unique_ptr<XClickEmulator> instance_;
    std::unique_ptr<Clicker> clicker_;
    XClickEmulator();

public:
    static XClickEmulator* getInstance();

    void mouseClick(int x, int y);

    ~XClickEmulator();
};

#endif // X_CLICKEMULATOR_H
