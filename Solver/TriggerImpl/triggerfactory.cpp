#include "triggerfactory.hpp"

#include "triggeractioneexecutor.hpp"
#include "triggerrecognizer.hpp"

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
    return new TriggerRecognizer;
}
