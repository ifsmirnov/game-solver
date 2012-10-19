#include "clicker.hpp"
#include <iostream>

int main() {
    Clicker clicker;
    int x, y;
    clicker.initClicker();
    while (1) {
        std::cin >> x >> y;
        if (x == -1  &&  y == -1) {
            break;
        }
        clicker.click(x, y);
    }
    clicker.deInitClicker();
}
