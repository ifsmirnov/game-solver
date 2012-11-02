#ifndef TRIGGERACTIONEEXECUTOR_HPP
#define TRIGGERACTIONEEXECUTOR_HPP

#include "app_headers/app_actionexecutor.hpp"
#include "triggerexternalstate.hpp"
#include "triggeraction.hpp"

class TriggerActioneExecutor : public AppActionExecutor
{
public:
    TriggerActioneExecutor();

    void execute(const AppExternalState *externalState,
                 const AppAction *action, SysEventsEmulator *emulator);
};

#endif // TRIGGERACTIONEEXECUTOR_HPP
