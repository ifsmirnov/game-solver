#include "minesfactory.hpp"

#include "TriggerImpl/triggeractioneexecutor.hpp"
#include "minesrecognizer.hpp"
#include "TriggerImpl/triggerinteractor.hpp"

MinesFactory::MinesFactory()
{
}

AppActionExecutor *MinesFactory::createExecutor()
{
    return new TriggerActioneExecutor;
}

AppInteractor *MinesFactory::createInteractor()
{
    return new TriggerInteractor;
}

AppRecognizer *MinesFactory::createRecognizer()
{
    return new MinesRecognizer;
}
