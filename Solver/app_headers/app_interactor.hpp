#ifndef APP_INTERACTOR_HPP
#define APP_INTERACTOR_HPP

#include "app_action.hpp"
#include "app_state.hpp"

class AppInteractor
{
public:
    AppInteractor() { }
    virtual ~AppInteractor() { }

public:
    virtual AppAction *nextAction(AppState*) = 0;

};

#endif // APP_INTERACTOR_HPP
