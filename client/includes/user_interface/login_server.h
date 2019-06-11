#ifndef LOGIN_SERVER_H
#define LOGIN_SERVER_H

#include <QWidget>

#include "login_mode.h"

class LoginServer : public Widget {
    Q_OBJECT

private:
    LoginMode & loginMode;
    virtual void connect_events();
    void login();

public:
    Login_server(LoginMode & loginMode, QWidget *parent = 0);
    virtual ~Login_server();
    
signals:
    void login_server_succesful();
    void login_server_fail();
};

#endif // LOGIN_SERVER_H
