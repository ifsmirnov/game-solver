#ifndef CLICKER_HPP_INCLUDED
#define CLICKER_HPP_INCLUDED

extern "C" {
#include "cclicker.h"
};


class Clicker {
public:
    Clicker();

    void click(int, int, int);

    void deInitClicker();
};

#endif
