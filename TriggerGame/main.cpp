#include <QApplication>

#include "game.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Game game;

    //game.setWindowTitle("5x5 super game");
    game.show();

    return app.exec();
}
