#ifndef APP_STATE_HPP
#define APP_STATE_HPP

#include "app_internalstate.hpp"
#include "app_externalstate.hpp"

#include <memory>

class AppState
{
public:
    AppState(AppInternalState* internalState, AppExternalState* externalState) :
        internalState_(internalState), externalState_(externalState)
        { }
    virtual ~AppState() { }

    AppInternalState *internalState() const { return internalState_.get(); }
    AppExternalState *externalState() const { return externalState_.get(); }

private:
    std::unique_ptr<AppInternalState> internalState_;
    std::unique_ptr<AppExternalState> externalState_;
};

#endif // APP_STATE_HPP
