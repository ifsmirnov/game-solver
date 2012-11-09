#include "triggerfactory.hpp"

#include "triggeractioneexecutor.hpp"
#include "triggerrecognizer.hpp"
#include "triggerinteractor.hpp"

TriggerFactory::TriggerFactory()
{
}

std::unique_ptr<AppActionExecutor> TriggerFactory::createExecutor()
{
    return std::unique_ptr<AppActionExecutor>(new TriggerActioneExecutor);
}

std::unique_ptr<AppInteractor> TriggerFactory::createInteractor()
{
    return std::unique_ptr<AppInteractor>(new TriggerInteractor);
}

std::unique_ptr<AppRecognizer> TriggerFactory::createRecognizer()
{
    return std::unique_ptr<AppRecognizer>(new TriggerRecognizer);
}
