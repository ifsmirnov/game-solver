#include "solver.hpp"

#include <iostream>

#include <app_headers/app_state.hpp>

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
    std::cerr << "Making move" << std::endl;

    AppState *recognizerResult = recognizer->recognize(printScreen());
    AppInternalState *internalState = recognizerResult->internalState();
    AppExternalState *externalState = recognizerResult->externalState();

    AppAction *action = interactor->nextAction(internalState);

    if (action->hasAction())
    {
        std::cerr << "executing..." << std::endl;
        executor->execute(externalState, action, emulator);
    }
}

void Solver::mousePressEvent(QMouseEvent *)
{
    makeMove();
}
