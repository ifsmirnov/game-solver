#include "triggerfactory.hpp"

#include "triggeractioneexecutor.hpp"

TriggerFactory::TriggerFactory()
{
}

AppActionExecutor *TriggerFactory::createExecutor()
{
    return new TriggerActioneExecutor;
}

AppInteractor *TriggerFactory::createInteractor()
{
    return new AppInteractor;
}

AppRecognizer *TriggerFactory::createRecognizer()
{
    return new AppRecognizer;
}
