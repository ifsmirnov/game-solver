#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <xdo.h>
#include "cclicker.h"

xdo_t* xdo;
Window gameWindow;
Display* dpy;

void c_click(int x, int y, int button)
{
    xdo_mousemove(xdo, x, y, 0);
    xdo_click(xdo, CURRENTWINDOW, button);
}

void c_initClicker()
{
    dpy = XOpenDisplay(NULL);
    xdo = xdo_new_with_opened_display(dpy, NULL, 0);
}


void c_deInitClicker()
{
    XCloseDisplay(dpy);
    free(xdo);
    free(dpy);
}


