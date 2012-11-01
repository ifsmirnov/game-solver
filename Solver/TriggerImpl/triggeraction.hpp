#ifndef TRIGGERACTION_HPP
#define TRIGGERACTION_HPP
#include "app_headers/app_action.hpp"
#include <vector>
#include <QPoint>

class TriggerAction
{
public:
    TriggerAction();

    bool hasAction() const;

    void setTurnsNum(int newNum);

    void setTurn(int index, QPoint turn);

    std::vector<QPoint> getTurns() const;

    ~TriggerAction();

private:
    std::vector<QPoint> turns_;
};

#endif // TRIGGERACTION_HPP
