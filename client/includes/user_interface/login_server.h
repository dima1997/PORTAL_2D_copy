#ifndef LOGIN_SERVER_H
#define LOGIN_SERVER_H

#include <QWidget>
#include <QCloseEvent>

class LoginMode;

class LoginServer : public QWidget {
private:
    LoginMode & loginMode;

    virtual void connect_events();
    void login();

public:
    LoginServer(LoginMode & loginMode, QWidget *parent = 0);
    virtual ~LoginServer();
    void quit();
};

#endif // LOGIN_SERVER_H
