#ifndef APP_ACTION_HPP
#define APP_ACTION_HPP

class AppAction
{
public:
    AppAction() { }
    virtual ~AppAction() { }

public:
    virtual bool hasAction() = 0;
};

#endif // APP_ACTION_HPP
