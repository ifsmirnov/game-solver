#include "triggeraction.hpp"


TriggerAction::TriggerAction()
{
}


void TriggerAction::setTurn(int index, QPoint turn)
{
    turns_[index] = turn;
}


void TriggerAction::setTurnsNum(int newNum)
{
    turns_.clear();
    turns_.resize(newNum, QPoint());
}

bool TriggerAction::hasAction() const
{
    return (turns_.size());
}


std::vector<QPoint> TriggerAction::getTurns() const
{
    return turns_;
}

TriggerAction::~TriggerAction()
{
}
