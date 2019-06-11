#ifndef LOGIN_SERVER_H
#define LOGIN_SERVER_H

#include <QWidget>

#include "login_mode.h"

class LoginServer : public QWidget {
    Q_OBJECT

private:
    LoginMode & loginMode;
    virtual void connect_events();
    void login();

public:
    LoginServer(LoginMode & loginMode, QWidget *parent = 0);
    virtual ~LoginServer();
    
signals:
    void login_server_success();
    void login_server_failed();
};

#endif // LOGIN_SERVER_H
