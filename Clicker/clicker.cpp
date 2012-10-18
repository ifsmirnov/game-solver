#include "clicker.hpp"

#include <iostream>

Clicker::Clicker()
    { }

void Clicker::click(int x, int y)
{
    std::cerr << "clicking on " << x << " " << y << std::endl;
    dpy = XOpenDisplay(0);
    root = DefaultRootWindow(dpy);
    XWarpPointer(dpy, None, root, 0, 0, 0, 0, x, y);
    memset(&event, 0x00, sizeof(event));
    event.type = ButtonPress;
    event.xbutton.button = Button1;
    event.xbutton.same_screen = True;
    XQueryPointer(dpy, RootWindow(dpy, DefaultScreen(dpy)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer(dpy, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }
    XSendEvent(dpy, PointerWindow, True, 0xfff, &event);
    event.type = ButtonRelease;
    event.xbutton.state = 0x100;
    XSendEvent(dpy, PointerWindow, True, 0xfff, &event);
    XFlush(dpy);
    XCloseDisplay(dpy);
}
