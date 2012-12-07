#include "clickcoordreciever.hpp"

#include <QMouseEvent>
#include <QPainter>
#include <iostream>

ClickCoordReciever::ClickCoordReciever(QWidget *parent, QImage image_, int number) :
    QWidget(0), image(image_), leftClicksToRecieve(number)
{
    // Solver is connected to this because this should be closed when solver is closed
    if (parent)
        QObject::connect(parent, SIGNAL(closed()), this, SLOT(close()));
    std::cerr << "created" << std::endl;
}
void ClickCoordReciever::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        QWidget::mousePressEvent(event);
    recievedClicks.push_back(event->pos());
    if (--leftClicksToRecieve == 0)
    {
        emit returnResult(recievedClicks);
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
