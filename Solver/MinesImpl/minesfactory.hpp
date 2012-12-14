#ifndef MINESFACTORY_HPP
#define MINESFACTORY_HPP

#include "app_headers/app_factory.hpp"

class MinesFactory : public AppFactory
{
public:
    MinesFactory();

public:
    AppActionExecutor *createExecutor();
    AppInteractor *createInteractor();
    AppRecognizer *createRecognizer();
};

#endif // MINESFACTORY_HPP
