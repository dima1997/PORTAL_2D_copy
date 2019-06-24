#ifndef LOGIN_MODE_H
#define LOGIN_MODE_H

#include <QWidget>
#include <QCloseEvent>

#include <connector/connector.h>

class LoginNew;
class LoginJoin;

class LoginMode : public QWidget {
private:
    LoginNew & loginNew;
    LoginJoin & loginJoin;
    Connector connector;
    bool isOpen;
    
    void config_new_game();
    void config_join_game();
    void connect_events();

public:
    LoginMode( 
        LoginNew & loginNew, 
        LoginJoin & loginJoin, 
        QWidget *parent = 0);
    virtual ~LoginMode();
    void set_connector(Connector & connector);
    virtual void closeEvent(QCloseEvent *event);
    void quit();
};

#endif // LOGIN_MODE_H
