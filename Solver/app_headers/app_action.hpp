#ifndef APP_ACTION_HPP
#define APP_ACTION_HPP
#include <memory>

class AppAction
{
public:
    AppAction() { }
    virtual ~AppAction() { }

public:
    virtual bool hasAction() const { return false; }
};

#endif // APP_ACTION_HPP
