#ifndef CLICKER_HPP
#define CLICKER_HPP

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

class Clicker
{
public:
    Clicker();

    void click(int, int);

private:
    Display* dpy;
    XEvent event;
    Window root;
};

#endif // CLICKER_HPP
