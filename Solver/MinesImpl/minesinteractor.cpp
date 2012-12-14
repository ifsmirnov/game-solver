#include "minesinteractor.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

MinesInteractor::MinesInteractor()
{
}

AppAction* MinesInteractor::nextAction(AppInternalState *internalState_)
{
    srand(time(0));
    MinesAction* ans = new MinesAction();
    MinesInternalState* internalState = dynamic_cast<MinesInternalState*>(internalState_);
    int unopenedColor = 9;
    int blown = 10;
    std::vector<QPoint> possibleTurns;
    for(int i = 0; i < internalState->getHeight(); i++)
        for(int j = 0; j < internalState->getWidth(); j++)
        {
            if(internalState->getField(i, j) == unopenedColor)
            {
                possibleTurns.push_back(QPoint(i, j));
            }
            if(internalState->getField(i, j) == blown)
            {
                return ans;
            }
        }
    if (possibleTurns.size() == 0)
    {
        return ans;
    }
    std::cout << possibleTurns.size() << std::endl;
    int turnsNum = 1;
    ans->setTurnsNum(turnsNum);
    for(int i = 0; i < turnsNum; i++)
    {
        ans->setTurn(i, possibleTurns[rand() % possibleTurns.size()], Qt::LeftButton);
    }
    return ans;
}
