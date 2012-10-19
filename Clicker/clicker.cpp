#include "clicker.hpp"
#include <iostream>

void Clicker::click(int x, int y) {
    c_click(x, y);
}


void Clicker::initClicker() {
    c_initClicker();
}


void Clicker::deInitClicker() {
    c_deInitClicker();
}

/*
int main() {
    int x, y;
    initClicker();
    while (1) {
        std::cin >> x >> y;
        if (x == -1  &&  y == -1) {
            break;
        }
        click(x, y);
    }
    deInitClicker();
}
*/
