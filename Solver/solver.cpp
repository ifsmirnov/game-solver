#include "solver.hpp"

Solver::Solver(QWidget *parent) :
    QWidget(parent)
{
}

Solver::Solver(AppFactory *factory_, SysEventsEmulator *emulator_, QWidget *parent) :
    QWidget(parent)
{
    emulator = emulator_;
    setApp(factory_);
}

void Solver::setApp(AppFactory *factory)
{
    executor = factory->createExecutor();
    interactor = factory->createInteractor();
    recognizer = factory->createRecognizer();
}

void Solver::setSysEventsEmulator(SysEventsEmulator *emulator_)
{
    emulator = emulator_;
}

QImage Solver::printScreen()
{
    return QImage();
}

void Solver::makeMove()
{
    AppState *state = 0;
    AppExternalState *externalState = 0;

    recognizer->recognize(printScreen(), state, externalState);

    AppAction *action = interactor->nextAction(state);

    if (action->hasAction())
        executor->execute(state, externalState, action, emulator);
}
