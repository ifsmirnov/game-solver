#include "triggerinteractor.hpp"

TriggerInteractor::TriggerInteractor()
{
}

AppAction* TriggerInteractor::nextAction(AppInternalState *internalState_)
{
    TriggerAction* ans = new TriggerAction();
    TriggerInternalState* internalState = dynamic_cast<TriggerInternalState*>(internalState_);
    int height = internalState->getHeight();
    int fieldsNum = height * internalState->getWidth();
    int coloredFields = 0;
    for(int i = 0; i < internalState->getHeight(); i++)
        for(int j = 0; j < internalState->getWidth(); j++)
            coloredFields += internalState->getField(i, j);
    int neededColor = 0;
    if(coloredFields > fieldsNum / 2)
    {
        neededColor = 1;
    }
    else
    {
        neededColor = 0;
        coloredFields = fieldsNum - coloredFields;
    }
    coloredFields -= fieldsNum / 2;
    ans->setTurnsNum(coloredFields);
    int currCoord = 0;
    for(int i = 0; i < coloredFields; i++)
    {
        while(internalState->getField(currCoord / height, currCoord % height) != neededColor)
        {
            currCoord++;
        }
        ans->setTurn(i, QPoint(currCoord / height, currCoord % height));
    }
    return ans;
}
