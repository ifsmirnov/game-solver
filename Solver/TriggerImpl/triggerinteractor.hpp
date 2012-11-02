#ifndef TRIGGERINTERACTOR_HPP
#define TRIGGERINTERACTOR_HPP
#include "app_headers/app_interactor.hpp"
#include "triggeraction.hpp"
#include "triggerinternalstate.hpp"

class TriggerInteractor : public AppInteractor
{
public:
    TriggerInteractor();

    AppAction* nextAction(AppInternalState *internalState_);

};

#endif // TRIGGERINTERACTOR_HPP
