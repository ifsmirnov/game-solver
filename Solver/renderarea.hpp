#ifndef RENDERAREA_HPP
#define RENDERAREA_HPP

#include <QWidget>
#include <QImage>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;
    void setImage(QImage);

public slots:
    void setDesktop();

private:
    QImage image;

};

#endif // RENDERAREA_HPP
