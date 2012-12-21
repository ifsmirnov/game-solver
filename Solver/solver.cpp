#include "solver.hpp"

#include <QtGui>
#include <QGridLayout>

#include <iostream>

#include <app_headers/app_state.hpp>
#include <MinesImpl/clickcoordreciever.hpp>
#include <MinesImpl/minescustomizer.hpp>
#include <MinesImpl/minesrecognizerhelper.hpp>
#include <gui/configdialog.hpp>

Solver::Solver(QWidget *parent) :
    QWidget(parent)
{
    // how to call basic constructor from some other one?
    createLayout();
}

Solver::Solver(AppFactory *factory_, SysEventsEmulator *emulator_, QWidget *parent) :
    QWidget(parent)
{
    helper = std::unique_ptr<AppRecognizerHelper>(new MinesRecognizerHelper());
    createLayout();
    emulator = std::unique_ptr<SysEventsEmulator>(emulator_);
    setApp(factory_);
}

void Solver::createLayout()
{
    QGridLayout *layout = new QGridLayout;

    comboBox = std::unique_ptr<QComboBox>(new QComboBox());
    configParser.loadConfig(comboBox.get());
    layout->addWidget(comboBox.get());

    startButton = std::unique_ptr<QPushButton>(new QPushButton("Solve!"));
    connect(startButton.get(), SIGNAL(released()), this, SLOT(startReleased()));
    layout->addWidget(startButton.get());

    configButton = std::unique_ptr<QPushButton>(new QPushButton("Add version"));
    connect(configButton.get(), SIGNAL(released()), this, SLOT(configReleased()));
    layout->addWidget(configButton.get());

    configDialog = std::unique_ptr<QDialog>(new ConfigDialog(this, &configParser));

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
    while(true)
    {
        std::unique_ptr<AppState> recognizerResult = recognizer->recognize(printScreen(), helper.get());
        AppInternalState *internalState = recognizerResult->internalState();
        AppExternalState *externalState = recognizerResult->externalState();
        std::unique_ptr<AppAction> action(interactor->nextAction(internalState));
        executor->execute(externalState, action.get(), emulator.get());
        if(!action->hasAction())
        {
            break;
        }
    }

}

void Solver::startReleased()
{
    //images = configParser.getImages(comboBox->currentText());
    std::string names[13] = {"opened", "1", "2", "3", "4", "5", "6", "7", "8", "unopened", "blown", "flag", "mine"};
    images.clear();
    for (int i = 0; i < 13; ++i)
    {
        images.push_back(QImage((std::string("img/") + names[i]).c_str()));
    }
    MinesRecognizerHelper* helper_ = dynamic_cast<MinesRecognizerHelper*>(helper.get());
    helper_->setImages(images);
    makeMove();
}

void Solver::configReleased()
{
    configDialog->setFixedSize(350, 700);
    configDialog->exec();
    configParser.loadConfig(comboBox.get());
}

void Solver::closeEvent(QCloseEvent *event)
{
    std::cerr << "close event called" << std::endl;
    delete(QWidget::layout());
    emit closed();
    event->accept();
}
