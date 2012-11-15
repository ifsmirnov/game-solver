#include <QApplication>

#include "solver.hpp"
#include <memory>
#include "TriggerImpl/triggerfactory.hpp"
#include "sys/x_clickemulator.h"
#include <valgrind/valgrind.h>

int main(int argc, char **argv)
{
    //Q_INIT_RESOURCE(application);
    QApplication app(argc, argv);
    std::unique_ptr<TriggerFactory> triggerFactory(new TriggerFactory);
    std::unique_ptr<SysEventsEmulator> emulator(XClickEmulator::getInstance());
    Solver solver(triggerFactory.get(), emulator.get());
    solver.show();
    return app.exec();
}
