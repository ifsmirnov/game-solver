#ifndef MINESINTERACTOR_HPP
#define MINESINTERACTOR_HPP
#include <app_headers/app_interactor.hpp>
#include "minesaction.hpp"
#include "minesinternalstate.hpp"


class MinesInteractor:public AppInteractor
{
public:
    MinesInteractor();

    AppAction* nextAction(AppInternalState *internalState_);
};

#endif // MINESINTERACTOR_HPP
