#include "minesinteractor.hpp"
#include <cstdlib>

MinesInteractor::MinesInteractor()
{
}

AppAction* MinesInteractor::nextAction(AppInternalState *internalState_)
{
    srand(time(0));
    MinesAction* ans = new MinesAction();
    MinesInternalState* internalState = dynamic_cast<MinesInternalState*>(internalState_);
    int unopenedColor = -1;
    std::vector<QPoint> possibleTurns;
    for(int i = 0; i < internalState->getHeight(); i++)
        for(int j = 0; j < internalState->getWidth(); j++)
            if(internalState->getField(i, j) == unopenedColor)
            {
                possibleTurns.push_back(QPoint(i, j));
            }
    if (possibleTurns.size() == 0)
    {
        return ans;
    }
    int turnsNum = 1;
    ans->setTurnsNum(turnsNum);
    for(int i = 0; i < turnsNum; i++)
    {
        ans->setTurn(i, possibleTurns[rand() % possibleTurns.size()], Qt::LeftButton);
    }
    return ans;
}
