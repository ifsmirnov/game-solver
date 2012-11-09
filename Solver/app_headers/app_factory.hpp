#ifndef APP_FACTORY_HPP
#define APP_FACTORY_HPP

#include "app_actionexecutor.hpp"
#include "app_interactor.hpp"
#include "app_recognizer.hpp"

class AppFactory
{
public:
    AppFactory() { }
    virtual ~AppFactory() { }

public:
    virtual std::unique_ptr<AppActionExecutor> createExecutor() = 0;
    virtual std::unique_ptr<AppInteractor> createInteractor() = 0;
    virtual std::unique_ptr<AppRecognizer> createRecognizer() = 0;

};

#endif // APP_FACTORY_HPP
