#ifndef CLICKCOORDRECIEVER_HPP
#define CLICKCOORDRECIEVER_HPP

#include <QWidget>

#include <vector>

class ClickCoordReciever : public QWidget
{
    Q_OBJECT
public:
    explicit ClickCoordReciever(QWidget *parent,
                                QImage image_,
                                int number);

private:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

signals:
    void returnResult(std::vector<QPoint>);

private:
    QImage image;
    std::vector<QPoint> recievedClicks;
    int leftClicksToRecieve;

};

#endif // CLICKCOORDRECIEVER_HPP
