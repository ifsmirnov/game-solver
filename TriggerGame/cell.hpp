#ifndef CELL_HPP
#define CELL_HPP

#include <QWidget>

class Cell : public QWidget
{
    Q_OBJECT
public:
    Cell(QWidget *parent = 0, int = -1, int = -1);

    QSize sizeHint() const;

    int color() const;
    int x() const;
    int y() const;
    void changeColor();

private:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

signals:
    void clicked();

private:
    int color_;
    int x_, y_;
};

#endif // CELL_HPP
