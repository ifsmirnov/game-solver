#ifndef APP_STATE_HPP
#define APP_STATE_HPP

#include "app_internalstate.hpp"
#include "app_externalstate.hpp"

class AppState
{
public:
    AppState(AppInternalState* internalState, AppExternalState* externalState) :
        internalState_(internalState), externalState_(externalState)
        { }
    virtual ~AppState() { }

    AppInternalState *internalState() const { return internalState_; }
    AppExternalState *externalState() const { return externalState_; }

private:
    AppInternalState *internalState_;
    AppExternalState *externalState_;
};

#endif // APP_STATE_HPP
