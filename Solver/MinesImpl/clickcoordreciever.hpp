#ifndef CLICKCOORDRECIEVER_HPP
#define CLICKCOORDRECIEVER_HPP

#include <QWidget>

#include <vector>

class ClickCoordReciever : public QWidget
{
    Q_OBJECT
public:
    explicit ClickCoordReciever(QWidget *parent = 0);

public:
    std::vector<QPoint> getClicks(const QImage&, int);

private:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    QImage image;
    std::vector<QPoint> recievedClicks;
    int leftClicksToRecieve;

};

#endif // CLICKCOORDRECIEVER_HPP
