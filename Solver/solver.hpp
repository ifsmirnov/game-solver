#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <QWidget>
#include <QImage>
#include <QComboBox>
#include <memory>
#include "configparser.hpp"
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
    std::unique_ptr<AppActionExecutor> executor;
    std::unique_ptr<AppInteractor> interactor;
    std::unique_ptr<AppRecognizer> recognizer;
    std::unique_ptr<SysEventsEmulator> emulator;
    std::unique_ptr<AppRecognizerHelper> helper;

    std::unique_ptr<RenderArea> renderArea;

    std::unique_ptr<QComboBox> comboBox;
    std::vector<QImage> images;
    ConfigParser configParser;
    void mousePressEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
};

#endif // SOLVER_HPP
