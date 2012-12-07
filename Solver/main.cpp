#include <QApplication>
#include <QtGui>
#include <QTimer>

#include "solver.hpp"

#include "TriggerImpl/triggerfactory.hpp"
#include "sys/x_clickemulator.h"

#include <iostream>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    std::unique_ptr<TriggerFactory> factory(new TriggerFactory);
    Solver solver(factory.get(), XClickEmulator::getInstance());
    solver.show();

    return app.exec();
}
