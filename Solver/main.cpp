#include <QApplication>

#include "solver.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Solver solver;
    solver.show();

    return app.exec();
}
