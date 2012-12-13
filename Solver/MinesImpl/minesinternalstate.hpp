#ifndef MINESINTERNALSTATE_HPP
#define MINESINTERNALSTATE_HPP
#include <app_headers/app_internalstate.hpp>
#include <vector>

class MinesInternalState: public AppInternalState
{
public:
    MinesInternalState(int height, int width);

    void setField(int x, int y, int data);

    int getField(int x, int y) const;

    int getHeight() const;

    int getWidth() const;

    ~MinesInternalState();

private:
    std::vector< std::vector<int> > field_;
    int height_, width_;
};

#endif // MINESINTERNALSTATE_HPP
