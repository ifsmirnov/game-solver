#include "triggerinternalstate.hpp"

TriggerInternalState::TriggerInternalState(int height, int width)
{
    field_.resize(height);
    for(int i = 0; i < height; i++)
    {
        field_[i].resize(width, 0);
    }
    height_ = height;
    width_ = width;
}


void TriggerInternalState::setField(int x, int y, int data)
{
    field_[x][y] = data;
}


int TriggerInternalState::getField(int x, int y) const
{
    return field_[x][y];
}

int TriggerInternalState::getHeight() const
{
    return height_;
}

int TriggerInternalState::getWidth() const
{
    return width_;
}
TriggerInternalState::~TriggerInternalState()
{

}
