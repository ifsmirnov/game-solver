#include "solver.hpp"

#include <QtGui>
#include <QGridLayout>

#include <iostream>
#include <cmath>

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
    emulator = std::unique_ptr<SysEventsEmulator>(emulator_);
    setApp(factory_);
}

void Solver::createLayout()
{
    QGridLayout *layout = new QGridLayout;
    renderArea = std::unique_ptr<RenderArea>(new RenderArea);
    layout->addWidget(renderArea.get());
    if(QWidget::layout() != 0)
    {
        delete(QWidget::layout());
    }
    setLayout(layout);
}

void Solver::setApp(AppFactory *factory)
{
    executor = std::unique_ptr<AppActionExecutor>(factory->createExecutor());
    interactor = std::unique_ptr<AppInteractor>(factory->createInteractor());
    recognizer = std::unique_ptr<AppRecognizer>(factory->createRecognizer());
}

void Solver::setSysEventsEmulator(SysEventsEmulator *emulator_)
{
    emulator = std::unique_ptr<SysEventsEmulator>(emulator_);
}


QImage Solver::printScreen()
{
    return QPixmap::grabWindow(QApplication::desktop()->winId()).toImage();
}

void Solver::makeMove()
{
    std::cerr << "Making move" << std::endl;

    std::unique_ptr<AppState> recognizerResult = recognizer->recognize(printScreen());
    AppInternalState *internalState = recognizerResult->internalState();
    AppExternalState *externalState = recognizerResult->externalState();

    std::unique_ptr<AppAction> action(interactor->nextAction(internalState));

    if (action->hasAction())
    {
        std::cerr << "executing..." << std::endl;
        executor->execute(externalState, action.get(), emulator.get());
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
    delete(QWidget::layout());
    emit closed();
    event->accept();
}
