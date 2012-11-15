#include "renderarea.hpp"

#include <QPainter>

#include <iostream>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent)
{
    delete(parent);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    if (!image.isNull())
    {
        std::cerr << "image.sz = " << image.width() << " " << image.height() << std::endl;
        QPainter painter(this);
        painter.drawImage(QRect(0, 0, width(), height()), image);

        std::cerr << "image drawn" << std::endl;
    }
}

void RenderArea::setImage(QImage image_)
{
    image = image_;
}

QSize RenderArea::sizeHint() const
{
    return QSize(320, 240);
}
