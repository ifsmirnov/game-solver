#include "minesinteractor.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "interactor/backtrack.h"

MinesInteractor::MinesInteractor()
{
}

AppAction* MinesInteractor::nextAction(AppInternalState *internalState_)
{
    srand(time(0));
    MinesInternalState* internalState = dynamic_cast<MinesInternalState*>(internalState_);

    const int unopened = 9;
    const int flag = 11;
    const int blown = 10;

    QPoint emptyCell(-1, -1);

    is_interactor::t_field field(internalState->getWidth(), std::vector<int>(internalState->getHeight()));
    for (int i = 0; i < internalState->getWidth(); ++i)
    {
        for (int j = 0; j < internalState->getHeight(); ++j)
        {
            int cell = internalState->getField(i, j);
            std::cerr << cell << " ";
            if (cell == unopened)
            {
                field[i][j] = is_interactor::cUnopened;
                if (emptyCell == QPoint(-1, -1))
                    emptyCell = QPoint(i, j);
            }
            else if (cell == flag)
                field[i][j] = is_interactor::cMine;
            else if (cell == blown)
                return new MinesAction;
            else if (cell >= 1 && cell <= 8)
                field[i][j] = cell;
            else
                field[i][j] = is_interactor::cUnknown;
        }
        std::cerr << std::endl << std::flush;
    }

    auto moves = is_interactor::determine(field, 1);

    if (!moves.first)
    {
        std::cerr << "Incorrect position!" << std::endl;
        return new MinesAction;
    }
    std::set<std::pair<int, int> > mines_ = moves.second.first, nomines_ = moves.second.second;
    std::vector<QPoint> mines, nomines;
    for (const auto i: mines_)
        mines.push_back(QPoint(i.first, i.second));
    for (const auto i: nomines_)
        nomines.push_back(QPoint(i.first, i.second));

    if (mines.empty() && nomines.empty())
    {
        if (emptyCell == QPoint(-1, -1))
        {
            std::cerr << "No possible move, error!" << std::endl;
            return new MinesAction;
        }
        nomines.push_back(emptyCell);
    }

    MinesAction *action = new MinesAction;
    for (auto i: mines)
    {
        std::cerr << "mine " << i.x() << " " << i.y() << std::endl;
        action->addTurn(i, Qt::RightButton);
    }
    for (auto i: nomines)
    {
        std::cerr << "no mine " << i.x() << " " << i.y() << std::endl;
        action->addTurn(i, Qt::LeftButton);
    }

    return action;
}
