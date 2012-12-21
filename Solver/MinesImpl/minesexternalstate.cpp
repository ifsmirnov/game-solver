#include "minesexternalstate.hpp"

MinesExternalState::MinesExternalState(int width, int height)
{
    coordinates_.assign(width, std::vector<QPoint>(height));
}


void MinesExternalState::setCoordinate(int x, int y, int coorX, int coorY)
{
    coordinates_[x][y] = QPoint(coorX, coorY);
}


QPoint MinesExternalState::getCoordinate(int x, int y) const
{
    return coordinates_[x][y];
}
