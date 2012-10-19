#ifndef TRIGGERFACTORY_HPP
#define TRIGGERFACTORY_HPP

#include "app_headers/app_factory.hpp"

class TriggerFactory : public AppFactory
{
public:
    TriggerFactory();

public:
    AppActionExecutor *createExecutor();
    AppInteractor *createInteractor();
    AppRecognizer *createRecognizer();
};

#endif // TRIGGERFACTORY_HPP
