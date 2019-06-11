#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include "login_new.h"
#include "login_join.h"

#include <connector/connector.h>

enum LoginEvent {
    NO_LOGIN,
    QUIT_LOGIN,
    NEW_LOGIN,
    JOIN_LOGIN
};

class Login : public QWidget {
public:
    Login(LoginEvent & loginEvent, 
          LoginNew & loginNew, 
          LoginJoin & loginJoin, 
          QWidget *parent = 0);
    virtual ~Login();
private:
    LoginEvent & loginEvent;
    LoginNew & loginNew;
    LoginJoin & loginJoin;
    void newGame();
    void joinGame();
    void connectEvents();
};

#endif // LOGIN_H