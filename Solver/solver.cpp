#include "solver.hpp"

#include <QtGui>
#include <QGridLayout>

#include <iostream>

#include <app_headers/app_state.hpp>

Solver::Solver(QWidget *parent) :
    QWidget(parent)
{
    // how to call basic constructor from some other one?
    createLayout();
}

Solver::Solver(AppFactory *factory_, SysEventsEmulator *emulator_, QWidget *parent) :
    QWidget(parent)
{
    createLayout();
    emulator = emulator_;
    setApp(factory_);
}

void Solver::createLayout()
{
    QGridLayout *layout = new QGridLayout;
    renderArea = new RenderArea;
    layout->addWidget(renderArea);
    setLayout(layout);
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
    return QPixmap::grabWindow(QApplication::desktop()->winId()).toImage();
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
    /*
    QImage image = printScreen();
    std::cerr << "pre img size:" << image.width() << " " << image.height() << std::endl;
    renderArea->setImage(image);
    update();
    std::cerr << "image set" << std::endl;
    */
}

void Solver::closeEvent(QCloseEvent *event)
{
    std::cerr << "close event called" << std::endl;
    emit closed();
    event->accept();
}
