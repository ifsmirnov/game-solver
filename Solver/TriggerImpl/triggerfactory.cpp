#include "triggerfactory.hpp"

#include "triggeractioneexecutor.hpp"
#include "triggerrecognizer.hpp"
#include "triggerinteractor.hpp"

TriggerFactory::TriggerFactory()
{
}

AppActionExecutor *TriggerFactory::createExecutor()
{
    return new TriggerActioneExecutor;
}

AppInteractor *TriggerFactory::createInteractor()
{
    return new TriggerInteractor;
}

AppRecognizer *TriggerFactory::createRecognizer()
{
    return new TriggerRecognizer;
}
