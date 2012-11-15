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
#include <QtGui>
#include <QGridLayout>

#include <iostream>

#include <app_headers/app_state.hpp>

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
    std::unique_ptr<AppActionExecutor> executor;
    std::unique_ptr<AppInteractor> interactor;
    std::unique_ptr<AppRecognizer> recognizer;
    SysEventsEmulator *emulator;
    std::unique_ptr<RenderArea> renderArea;
    std::unique_ptr<QGridLayout> layout;

    void mousePressEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
};

#endif // SOLVER_HPP
