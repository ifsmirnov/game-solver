#ifndef CLICKER_HPP_INCLUDED
#define CLICKER_HPP_INCLUDED

extern "C" {
#include "cclicker.h"
};


class Clicker {
public:
    void click(int, int);

    void initClicker();

    void deInitClicker();
};

#endif
