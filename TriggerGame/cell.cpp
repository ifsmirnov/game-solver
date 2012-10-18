#include "cell.hpp"

#include <iostream>

#include <QPainter>

Cell::Cell(QWidget *parent, int x, int y) :
    QWidget(parent), x_(x), y_(y)
{
    color_ = 0;
}

QSize Cell::sizeHint() const
{
    return QSize(50, 50);
}

int Cell::color() const
{
    return color_;
}
int Cell::x() const
{
    return x_;
}
int Cell::y() const
{
    return y_;
}

void Cell::changeColor()
{
    color_ = 1 - color_;
    update();
}

void Cell::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(color_ ? Qt::red : Qt::blue);
    painter.setPen(Qt::NoPen);

    painter.drawRect(0, 0, width(), height());
}

void Cell::mousePressEvent(QMouseEvent *)
{
    std::cerr << x() << " " << y() << ": Recieved click" << std::endl;
    changeColor();
    clicked();
    //dynamic_cast<Game*>(parentWidget())->checkWin();} // i want to do dynamic_cast, but
    // it will cause cyclic dependencies
    // signal-slots?
}
