#include "minesinternalstate.hpp"

MinesInternalState::MinesInternalState(int height, int width)
{
    field_.resize(height);
    for(int i = 0; i < height; i++)
    {
        field_[i].resize(width, 0);
    }
    height_ = height;
    width_ = width;
}


void MinesInternalState::setField(int x, int y, int data)
{
    field_[x][y] = data;
}


int MinesInternalState::getField(int x, int y) const
{
    return field_[x][y];
}

int MinesInternalState::getHeight() const
{
    return height_;
}

int MinesInternalState::getWidth() const
{
    return width_;
}

MinesInternalState::~MinesInternalState()
{

}
