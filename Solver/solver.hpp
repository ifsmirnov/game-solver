#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QWidget>
#include <QImage>

#include "app_headers/app_factory.hpp"
#include "app_headers/app_actionexecutor.hpp"
#include "app_headers/app_interactor.hpp"
#include "app_headers/app_recognizer.hpp"
#include "sys/emulator.hpp"

class Solver : public QWidget
{
    Q_OBJECT
public:
    explicit Solver(QWidget *parent = 0);
    Solver(AppFactory *factory, SysEventsEmulator *emulator_, QWidget *parent = 0);

public:
    void setApp(AppFactory *factory);
    void setSysEventsEmulator(SysEventsEmulator *emulator_);

private slots:
    void makeMove();

private:
    QImage printScreen();

private:
    // TODO - change to std::unique_ptr; now memory leaks are possible
    AppActionExecutor *executor;
    AppInteractor *interactor;
    AppRecognizer *recognizer;
    SysEventsEmulator *emulator;

    void mousePressEvent(QMouseEvent *);
};

#endif // SOLVER_HPP
