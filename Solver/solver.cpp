#include "solver.hpp"

#include <QtGui>
#include <QGridLayout>

#include <iostream>

#include <app_headers/app_state.hpp>
#include <MinesImpl/clickcoordreciever.hpp>
#include <MinesImpl/minescustomizer.hpp>
#include <MinesImpl/minesrecognizerhelper.hpp>
#include <gui/configdialog.hpp>

int Solver::MAX_WIDTH = 90;
int Solver::MAX_HEIGHT = 90;

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

    fieldWidth = new QLineEdit("width");
    fieldHeight = new QLineEdit("height");
    warmUpEdit = new QLineEdit("Warming up turns num");
    layout->addWidget(fieldWidth);
    layout->addWidget(fieldHeight);
    layout->addWidget(warmUpEdit);

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
        usleep(200 * 1000);
        std::unique_ptr<AppState> recognizerResult = recognizer->recognize(printScreen(), helper.get());
        (dynamic_cast<MinesRecognizerHelper*>(helper.get()))->setFirstMove(false);
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
    QMessageBox qmBox;
    bool result = true;
    int width = fieldWidth->text().toInt(&result);
    if (!result  ||  width <= 0  ||  width >= MAX_WIDTH)
    {
        qmBox.setText("Incorrect width");
        qmBox.exec();
        return;
    }
    int height = fieldHeight->text().toInt(&result);
    if (!result  ||  height <= 0  ||  height >= MAX_HEIGHT)
    {
        qmBox.setText("Incorrect height");
        qmBox.exec();
        return;
    }
    int warmUpTurns = warmUpEdit->text().toInt(&result);
    if (!result  ||  warmUpTurns < 0  ||  warmUpTurns > width * height)
    {
        qmBox.setText("Incorrect warm up");
        qmBox.exec();
        return;
    }
    images = configParser.getImages(comboBox->currentText());
    MinesRecognizerHelper* helper_ = dynamic_cast<MinesRecognizerHelper*>(helper.get());
    helper_->setWidth(width);
    helper_->setHeight(height);
    helper_->setImages(images);
    helper_->setWarmUpTurns(warmUpTurns);
    helper_->setFirstMove(true);
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
