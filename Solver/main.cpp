#include <QApplication>
#include <QtGui>

#include "solver.hpp"

#include "TriggerImpl/triggerfactory.hpp"
#include "sys/x_clickemulator.h"

#include "MineImpl/minesfielddetector.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <QTimer>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QImage image = QPixmap::grabWindow(QApplication::desktop()->winId()).toImage();

    MinesFieldDetector mfd;
    std::string s = "abcabcabd";

    std::pair<int, std::vector<int>> res = mfd.longestFrequentSubstrs(s.begin(), s.end(), 2);
    std::cout << res.first << std::endl;

    QWidget *widget = new QWidget;
    widget->show();

    QTimer *timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), widget, SLOT(close()));
    timer->setInterval(0);
    timer->start();

    return app.exec();
}
