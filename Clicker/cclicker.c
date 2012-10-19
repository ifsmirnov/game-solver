#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <xdo.h>
#include "cclicker.h"

xdo_t* xdo;
Window gameWindow;
Display* dpy;

void c_click(int x, int y)
{
    xdo_window_activate(xdo, gameWindow);
    //XFlush(dpy);
    xdo_mousemove_relative_to_window(xdo, gameWindow, x, y);
    xdo_click(xdo, CURRENTWINDOW, 1);
    //XFlush(dpy);
}

void c_initClicker()
{
    dpy = XOpenDisplay(NULL);
    xdo = xdo_new_with_opened_display(dpy, NULL, 0);
    xdo_window_select_with_click(xdo, &gameWindow);
}


void c_deInitClicker()
{
    XCloseDisplay(dpy);
    free(xdo);
}

/*
int main()
{
    initClicker();
    int i, j;
    while (1) {
        scanf("%d %d", &i, &j);
        if (i == -1  &&  j == -1) {
            break;
        }
        click(i, j);
    }
}
*/
