#include <QApplication>

#include "solver.hpp"

#include "TriggerImpl/triggerfactory.hpp"
#include "sys/x_clickemulator.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Solver solver(new TriggerFactory, XClickEmulator::getInstance());
    solver.show();

    return app.exec();
}
