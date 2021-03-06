#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QWidget>
#include <QImage>

#include "app_headers/app_factory.hpp"
#include "app_headers/app_actionexecutor.hpp"
#include "app_headers/app_interactor.hpp"
#include "app_headers/app_recognizer.hpp"
#include "sys/emulator.hpp"
#include "renderarea.hpp"

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

signals:
    void closed();

private:
    QImage printScreen();
    void createLayout();

private:
    // TODO - change to std::unique_ptr; now memory leaks are possible
    AppActionExecutor *executor;
    AppInteractor *interactor;
    AppRecognizer *recognizer;
    SysEventsEmulator *emulator;

    RenderArea *renderArea;

    void mousePressEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
};

#endif // SOLVER_HPP
