#ifndef RENDERAREA_HPP
#define RENDERAREA_HPP

#include <QWidget>
#include <QImage>
#include <memory>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);

    void setImage(QImage);
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const;

private:
    QImage image;

};

#endif // RENDERAREA_HPP
