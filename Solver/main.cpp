#include <QApplication>

#include "solver.hpp"

#include "TriggerImpl/triggerfactory.hpp"
#include "sys/stupidemulator.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Solver solver(new TriggerFactory, new StupidEmulator);
    solver.show();

    return app.exec();
}
