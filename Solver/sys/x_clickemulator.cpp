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
    if (button == Qt::LeftButton)
        clicker_->click(x, y, 1); //left button
    else
        clicker_->click(x, y, 3); //right button
}

XClickEmulator::~XClickEmulator()
{
    delete clicker_;
    instance_flag_ = false;
}
