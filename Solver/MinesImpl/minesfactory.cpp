#include "minesfactory.hpp"

#include "minesactionexecutor.hpp"
#include "minesrecognizer.hpp"
#include "minesinteractor.hpp"

MinesFactory::MinesFactory()
{
}

AppActionExecutor *MinesFactory::createExecutor()
{
    return new MinesActionExecutor;
}

AppInteractor *MinesFactory::createInteractor()
{
    return new MinesInteractor;
}

AppRecognizer *MinesFactory::createRecognizer()
{
    return new MinesRecognizer;
}
