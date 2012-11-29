#include <QApplication>

#include "solver.hpp"

#include "TriggerImpl/triggerfactory.hpp"
#include "sys/x_clickemulator.h"

int main(int argc, char **argv)
{
    std::unique_ptr<TriggerFactory> factory(new TriggerFactory);
    QApplication app(argc, argv);


    Solver solver(factory.get(), XClickEmulator::getInstance());
    solver.show();

    return app.exec();
}
