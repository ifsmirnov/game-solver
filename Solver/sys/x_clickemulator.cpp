#include "x_clickemulator.h"

XClickEmulator::XClickEmulator()
{
    instance_ = 0;
}

SysEventsEmulator* XClickEmulator::Instance()
{
    if(instance_ == 0)
    {
        clicker_ = new Clicker;
        //clicker_->instance_ = this;
    }
    return instance_;
}

XClickEmulator::~XClickEmulator()
{
    clicker_->deInitClicker();
    delete clicker_;
}

void XClickEmulator::mouseClick(int x, int y)
{
    clicker_->click(x, y);
}

