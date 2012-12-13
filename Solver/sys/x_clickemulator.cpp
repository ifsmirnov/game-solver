#include "x_clickemulator.h"
#include <iostream>

bool XClickEmulator::instance_flag_ = false;

XClickEmulator* XClickEmulator::instance_ = NULL;

XClickEmulator::XClickEmulator()
{
    clicker_ = new Clicker();
}

XClickEmulator* XClickEmulator::getInstance()
{
    if(!instance_flag_)
    {
        instance_ = new XClickEmulator();
        instance_flag_ = true;
    }
    return instance_;
}

void XClickEmulator::mouseClick(int x, int y, int button)
{
    clicker_->click(x, y, button);
}

XClickEmulator::~XClickEmulator()
{
    delete clicker_;
    instance_flag_ = false;
}
