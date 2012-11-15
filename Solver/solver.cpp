#include "solver.hpp"



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
    layout = std::unique_ptr<QGridLayout>(new QGridLayout);
    renderArea = std::unique_ptr<RenderArea>(new RenderArea);
    layout->addWidget(renderArea.get());
    setLayout(layout.get());
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

    std::unique_ptr<AppState> recognizerResult = recognizer->recognize(printScreen());
    AppInternalState *internalState = recognizerResult->internalState();
    AppExternalState *externalState = recognizerResult->externalState();

    std::unique_ptr<AppAction> action = interactor->nextAction(internalState);

    if (action->hasAction())
    {
        std::cerr << "executing..." << std::endl;
        executor->execute(externalState, action.get(), emulator);
    }
}

void Solver::mousePressEvent(QMouseEvent *event)
{
    makeMove();
    /*
    QImage image = printScreen();
    std::cerr << "pre img size:" << image.width() << " " << image.height() << std::endl;
    renderArea->setImage(image);
    update();
    std::cerr << "image set" << std::endl;
    */
    delete(event);
}

void Solver::closeEvent(QCloseEvent *event)
{
    std::cerr << "close event called" << std::endl;
    emit closed();
    event->accept();
    delete(event);

}
