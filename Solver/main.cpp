#include <QApplication>

#include "solver.hpp"
#include <memory>
#include "TriggerImpl/triggerfactory.hpp"
#include "sys/x_clickemulator.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    std::unique_ptr<TriggerFactory> triggerFactory(new TriggerFactory);
    Solver solver(triggerFactory.get(), XClickEmulator::getInstance());
    solver.show();

    return app.exec();
}
