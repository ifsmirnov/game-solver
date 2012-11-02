#ifndef APP_ACTION_HPP
#define APP_ACTION_HPP

class AppAction
{
public:
    AppAction() { }
    virtual ~AppAction() { }

public:
    virtual bool hasAction() const { return false; }
};

#endif // APP_ACTION_HPP
