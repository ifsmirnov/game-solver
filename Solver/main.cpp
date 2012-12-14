#include <QApplication>
#include <QtGui>
#include <QTimer>

#include "solver.hpp"

#include "MinesImpl/minesfactory.hpp"
#include "sys/x_clickemulator.h"

#include <iostream>


#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNodeList>
#include <QtXml/QDomNode>
#include <QString>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>



int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    std::unique_ptr<MinesFactory> factory(new MinesFactory);
    Solver solver(factory.get(), XClickEmulator::getInstance());
    solver.show();

    return app.exec();
}
