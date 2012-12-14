#include "minesactionexecutor.hpp"

MinesActionExecutor::MinesActionExecutor()
{
}

void MinesActionExecutor::execute(const AppExternalState *extState_,
                                const AppAction *action_, SysEventsEmulator *emulator)
{
    const MinesAction* action = dynamic_cast<const MinesAction*>(action_);
    const MinesExternalState* extState = dynamic_cast<const MinesExternalState*>(extState_);
    if(action->hasAction())
    {
        std::vector<std::pair<QPoint, int> > turns = action->getTurns();
        QPoint mouseTarget;
        for(int i = 0; i < (int)turns.size(); i++)
        {
            mouseTarget = extState->getCoordinate(turns[i].first.x(), turns[i].first.y());
            emulator->mouseClick(mouseTarget.x(), mouseTarget.y(), turns[i].second);
            usleep(100 * 1000);
        }
    }
    else
    {
        //как-нибудь завершить игру
    }
}
