#include "solver.hpp"

#include <QtGui>
#include <QGridLayout>

#include <iostream>
#include <cmath>

#include <app_headers/app_state.hpp>
#include "MinesImpl/clickcoordreciever.hpp"

Solver::Solver(QWidget *parent) :
    QWidget(parent)
{
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

void Solver::f1()
{
    ClickCoordReciever *clickCoordReciever = new ClickCoordReciever(this, printScreen(), 2);
    QObject::connect(clickCoordReciever, SIGNAL(returnResult(std::vector<QPoint>)), this, SLOT(f2(std::vector<QPoint>)));
    clickCoordReciever->show();
    clickCoordReciever->setWindowState(Qt::WindowFullScreen);
    clickCoordReciever->update();
}
void Solver::f2(std::vector<QPoint> res)
{
    for (auto i: res)
        std::cerr << i.x() << " " << i.y() << std::endl;
}

void Solver::mousePressEvent(QMouseEvent *)
{
    f1();
    return;

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
