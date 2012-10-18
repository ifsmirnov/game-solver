#ifndef GAME_HPP
#define GAME_HPP

#include <QWidget>
#include "cell.hpp"

#include <vector> // should be replaced with QArray
#include <iostream> // should be replaced with QStream too

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = 0);

private slots:
    bool checkWin() const;

private:
    std::vector<std::vector<Cell*> > grid;
    void paintEvent(QPaintEvent *);

    void initRandom() const;

};

#endif // GAME_HPP
