#include "triggerexternalstate.hpp"

TriggerExternalState::TriggerExternalState(int height, int width)
{
    coordinates_.resize(height);
    for(int i = 0; i < height; i++)
    {
        coordinates_[i].resize(width);
    }
}


void TriggerExternalState::setCoordinate(int x, int y, int coorX, int coorY)
{
    coordinates_[x][y] = QPoint(coorX, coorY);
}


QPoint TriggerExternalState::getCoordinate(int x, int y) const
{
    return coordinates_[x][y];
}
