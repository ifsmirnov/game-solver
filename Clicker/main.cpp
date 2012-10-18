#include "clicker.hpp"

#include <iostream>

int main()
{
    Clicker clicker;

    int x, y;
    while (std::cin >> x >> y)
    {
        std::cerr << "try to click on " << x << " " << y << std::endl;
        clicker.click(x, y);
    }

    return 0;
}
