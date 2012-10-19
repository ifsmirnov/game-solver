#include "triggeractioneexecutor.hpp"

#include "sys/emulator.hpp"

TriggerActioneExecutor::TriggerActioneExecutor()
{
}

void TriggerActioneExecutor::execute(const AppExternalState *,
                                const AppAction *, SysEventsEmulator *emulator)
{
    emulator->mouseClick(123, 456);
}
