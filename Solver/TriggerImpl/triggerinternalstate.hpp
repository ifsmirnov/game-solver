#ifndef TRIGGERINTERNALSTATE_HPP
#define TRIGGERINTERNALSTATE_HPP
#include "app_headers/app_internalstate.hpp"
#include <vector>

class TriggerInternalState: public AppInternalState
{
public:
    TriggerInternalState(int height, int width);

    void setField(int x, int y, int data);

    int getField(int x, int y) const;

    int getHeight() const;

    int getWidth() const;

    ~TriggerInternalState();

private:
    std::vector< std::vector<int> > field_;
    int height_, width_;
};

#endif // TRIGGERINTERNALSTATE_HPP
