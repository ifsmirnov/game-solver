#include "minesaction.hpp"

MinesAction::MinesAction()
{
}


void MinesAction::setTurn(int index, QPoint turn, int button)
{
    turns_[index] = std::pair<QPoint, int>(turn, button);
}
void MinesAction::addTurn(QPoint turn, int button)
{
    turns_.push_back(std::pair<QPoint, int>(turn, button));
}


void MinesAction::setTurnsNum(int newNum)
{
    turns_.clear();
    turns_.resize(newNum);
}

bool MinesAction::hasAction() const
{
    return (turns_.size());
}


std::vector<std::pair<QPoint, int> > MinesAction::getTurns() const
{
    return turns_;
}

MinesAction::~MinesAction()
{
}
