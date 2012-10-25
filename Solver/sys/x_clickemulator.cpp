#include "x_clickemulator.h"

XClickEmulator XClickEmulator::XClickEmulator()
{
    instance_ = 0;
}

XClickEmulator* XClickEmulator::Instance()
{
    if(instance_ == 0)
    {
        clicker_ = new Clicker;
        clicker_.
        instance_ = this;
    }
    return clicker;
}

XClickEmulator::~XClickEmulator()
{
    clicker_->deInitClicker();
    free(clicker);
}

void XClickEmulator::mouseClick(int x, int y)
{
    clicker->click(x, y);
}

