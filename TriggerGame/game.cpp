#include "game.hpp"

#include <QGridLayout>
#include <QPainter>

#include <cstdlib>
#include <cassert>

#include <fcntl.h>
#include <unistd.h>

Game::Game(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *layout = new QGridLayout;

    initRandom();

    int w = 5, h = 6;
    grid.resize(w);
    for (int i = 0; i < w; i++)
    {
        grid[i].resize(h);
        for (int j = 0; j < h; j++)
        {
            grid[i][j] = new Cell(this, i, j);
            if (rand() % 3 < 2)
            {
                grid[i][j]->changeColor();
            }
            layout->addWidget(grid[i][j], i, j);
            /*QObject::connect(grid[i][j], SIGNAL(clicked()),
                             this, SLOT(checkWin()));*/
        }
    }

    setLayout(layout);
}

bool Game::checkWin() const
{
    int cnt[2] = {0,0};
    for (const auto &i: grid)
        for (const auto &j: i)
            ++cnt[j->color()];
    if (cnt[0] == cnt[1])
    {
        std::cerr << "Game is in a winning state" << std::endl;
        return true;
    }
    std::cerr << "Game is not in a winning state" << std::endl;
    return false;
}

void Game::paintEvent(QPaintEvent *)
{
    static bool currentWin = false;
    static int depth = 0;
    ++depth;
    if (checkWin())
    {
        QPainter painter(this);
        painter.setBrush(Qt::green);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, width(), height());
        //std::cerr << "painted " << rand() << std::endl;

        if (!currentWin) // how do people usually implement this flag?
        {
            currentWin = true;
            update();
        }
    }
    else
    {
        if (currentWin)
        {
            currentWin = false;
            update();
        }
    }
    --depth;
}

void Game::initRandom() const
{
    int fd = open("/dev/urandom", O_RDONLY);
    int x;
    assert(read(fd, (void*)(&x), 4) == 4);
    srand(x);
    ::close(fd);
}
