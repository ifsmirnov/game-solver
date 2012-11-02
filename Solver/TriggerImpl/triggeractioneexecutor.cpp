#include "triggeractioneexecutor.hpp"
#include "sys/emulator.hpp"

TriggerActioneExecutor::TriggerActioneExecutor()
{
}

void TriggerActioneExecutor::execute(const AppExternalState *extState_,
                                const AppAction *action_, SysEventsEmulator *emulator)
{
    const TriggerAction* action = dynamic_cast<const TriggerAction*>(action_);
    const TriggerExternalState* extState = dynamic_cast<const TriggerExternalState*>(extState_);
    if(action->hasAction())
    {
        std::vector<QPoint> turns = action->getTurns();
        QPoint mouseTarget;
        for(int i = 0; i < (int)turns.size(); i++)
        {
            mouseTarget = extState->getCoordinate(turns[i].x(), turns[i].y());
            emulator->mouseClick(mouseTarget.x(), mouseTarget.y());
        }
    }
    else
    {
        //как-нибудь завершить игру
    }
}
