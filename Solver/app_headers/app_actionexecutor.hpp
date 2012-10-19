#ifndef APP_ACTIONEXECUTOR_HPP
#define APP_ACTIONEXECUTOR_HPP

#include "app_action.hpp"
#include "app_externalstate.hpp"
#include "sys/emulator.hpp"

class AppActionExecutor
{
public:
    AppActionExecutor() { }
    virtual ~AppActionExecutor() { }

    virtual void execute(const AppExternalState *externalState,
                 const AppAction *action, SysEventsEmulator *emulator) = 0;
};

#endif // APP_ACTIONEXECUTOR_HPP
