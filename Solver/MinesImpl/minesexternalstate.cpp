#include "minesexternalstate.hpp"

MinesExternalState::MinesExternalState(int height, int width)
{
    coordinates_.resize(height);
    for(int i = 0; i < height; i++)
    {
        coordinates_[i].resize(width);
    }
}


void MinesExternalState::setCoordinate(int x, int y, int coorX, int coorY)
{
    coordinates_[x][y] = QPoint(coorX, coorY);
}


QPoint MinesExternalState::getCoordinate(int x, int y) const
{
    return coordinates_[x][y];
}
