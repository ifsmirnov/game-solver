#include "x_clickemulator.h"

bool XClickEmulator::instance_flag_ = false;

std::unique_ptr<XClickEmulator> XClickEmulator::instance_ = NULL;

XClickEmulator::XClickEmulator()
{
    clicker_ = std::unique_ptr<Clicker>(new Clicker());
}

XClickEmulator* XClickEmulator::getInstance()
{
    if(!instance_flag_)
    {
        instance_ = std::unique_ptr<XClickEmulator>(new XClickEmulator());
        instance_flag_ = true;
    }
    return instance_.get();
}

void XClickEmulator::mouseClick(int x, int y)
{
    clicker_->click(x, y);
}

XClickEmulator::~XClickEmulator()
{
    instance_flag_ = false;
}
