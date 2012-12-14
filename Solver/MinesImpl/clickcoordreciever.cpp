#include "clickcoordreciever.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <QApplication>
#include <iostream>

ClickCoordReciever::ClickCoordReciever(QWidget *parent) :
    QWidget(parent)
{
}
void ClickCoordReciever::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        QWidget::mousePressEvent(event);
    recievedClicks.push_back(event->pos());
    if (--leftClicksToRecieve == 0)
    {
        close();
    }
}
void ClickCoordReciever::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
    painter.setPen(Qt::red);
    painter.setFont(QFont(QString("sans"), 48, 1, false));
    painter.drawText(100, 100, 500, 200, 0, QString("PRINT SCREEN!"));
}
std::vector<QPoint> ClickCoordReciever::getClicks(const QImage& image_, int clicksNumber)
{
    image = image_;
    leftClicksToRecieve = clicksNumber;
    recievedClicks.clear();
    setWindowState(Qt::WindowFullScreen);
    show();
    while (leftClicksToRecieve)
        QApplication::processEvents();
    return recievedClicks;
}
