#ifndef TRIGGEREXTERNALSTATE_HPP
#define TRIGGEREXTERNALSTATE_HPP
#include "app_headers/app_externalstate.hpp"
#include <vector>
#include <QPoint>

class TriggerExternalState : public AppExternalState
{
public:
    TriggerExternalState(int height, int width);

    void setCoordinate(int x, int y, int coorX, int coorY);

    QPoint getCoordinate(int x, int y) const;


private:

    //containes coordinates for button (x,y) on screen relative to screen
    std::vector<std::vector <QPoint> > coordinates_;

};

#endif // TRIGGEREXTERNALSTATE_HPP
