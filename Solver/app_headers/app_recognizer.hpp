#ifndef APP_RECOGNIZER_HPP
#define APP_RECOGNIZER_HPP

#include <QImage>

#include "app_externalstate.hpp"
#include "app_state.hpp"

class AppRecognizer
{
public:
    AppRecognizer() { }
    virtual ~AppRecognizer() { }

public:
    virtual void recognize(QImage image, AppState *state, AppExternalState *externalState) = 0;
};

#endif // APP_RECOGNIZER_HPP
