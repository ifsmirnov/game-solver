#ifndef TRIGGERFACTORY_HPP
#define TRIGGERFACTORY_HPP

#include "app_headers/app_factory.hpp"

class TriggerFactory : public AppFactory
{
public:
    TriggerFactory();

public:
    std::unique_ptr<AppActionExecutor> createExecutor();
    std::unique_ptr<AppInteractor> createInteractor();
    std::unique_ptr<AppRecognizer> createRecognizer();
};

#endif // TRIGGERFACTORY_HPP
