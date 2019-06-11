#ifndef LOGIN_MODE_H
#define LOGIN_MODE_H

#include <QWidget>

#include "login_new.h"
#include "login_join.h"

#include <connector/connector.h>

class LoginMode : public QWidget {
    Q_OBJECT

public:
    LoginMode( 
        LoginNew & loginNew, 
        LoginJoin & loginJoin, 
        QWidget *parent = 0);
    virtual ~Login();
    void setConnector(Connector & connector);

private:
    LoginNew & loginNew;
    LoginJoin & loginJoin;
    void newGame();
    void joinGame();
    void connectEvents();

signals:
    void login_mode_new();
    void login_mode_join();
    void login_mode_failed();
};

#endif // LOGIN_MODE_H
