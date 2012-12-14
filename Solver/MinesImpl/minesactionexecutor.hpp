#ifndef MINESACTIONEXECUTOR_HPP
#define MINESACTIONEXECUTOR_HPP
#include <app_headers/app_actionexecutor.hpp>
#include "minesaction.hpp"
#include "minesexternalstate.hpp"

class MinesActionExecutor:public AppActionExecutor
{
    MinesActionExecutor();

    void execute(const AppExternalState *externalState,
                 const AppAction *action, SysEventsEmulator *emulator);
};

#endif // MINESACTIONEXECUTOR_HPP
