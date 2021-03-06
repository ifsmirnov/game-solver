#ifndef APP_RECOGNIZER_HPP
#define APP_RECOGNIZER_HPP

#include "app_state.hpp"
#include "app_internalstate.hpp"
#include "app_externalstate.hpp"

#include <QImage>

#include <utility>

class AppRecognizer
{
public:
    AppRecognizer() { }
    virtual ~AppRecognizer() { }

public:
    virtual AppState *recognize(QImage)
    {
        return new AppState(new AppInternalState, new AppExternalState);
    }
};

#endif // APP_RECOGNIZER_HPP
