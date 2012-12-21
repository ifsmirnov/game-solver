#ifndef MINESEXTERNALSTATE_HPP
#define MINESEXTERNALSTATE_HPP
#include <app_headers/app_externalstate.hpp>
#include <vector>
#include <QPoint>

class MinesExternalState : public AppExternalState
{
public:
    MinesExternalState(int width, int height);

    void setCoordinate(int x, int y, int coorX, int coorY);

    QPoint getCoordinate(int x, int y) const;


private:

    std::vector<std::vector <QPoint> > coordinates_;
};

#endif // MINESEXTERNALSTATE_HPP
