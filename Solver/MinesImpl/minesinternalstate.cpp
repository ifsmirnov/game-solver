#include "minesinternalstate.hpp"

MinesInternalState::MinesInternalState(int width, int height)
{
    field_.assign(width, std::vector<int>(height));
    width_ = width;
    height_ = height;
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
