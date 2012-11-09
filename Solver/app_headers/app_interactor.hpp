#ifndef APP_INTERACTOR_HPP
#define APP_INTERACTOR_HPP

#include "app_action.hpp"
#include "app_internalstate.hpp"

class AppInteractor
{
public:
    AppInteractor() { }
    virtual ~AppInteractor() { }

public:
    virtual std::unique_ptr<AppAction> nextAction(AppInternalState* ) { return std::unique_ptr<AppAction>(new AppAction); }

};

#endif // APP_INTERACTOR_HPP
