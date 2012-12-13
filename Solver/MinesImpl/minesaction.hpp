#ifndef MINESACTION_HPP
#define MINESACTION_HPP
#include <utility>
#include <vector>
#include <QPoint>
#include <app_headers/app_action.hpp>

class MinesAction: public AppAction
{
public:
    MinesAction();

    bool hasAction() const;

    void setTurnsNum(int newNum);

    void setTurn(int index, QPoint turn, int button);

    std::vector<std::pair<QPoint, int> > getTurns() const;

    ~MinesAction();

private:
    std::vector<std::pair<QPoint, int> > turns_;
};

#endif // MINESACTION_HPP
