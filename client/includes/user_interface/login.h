#ifndef LOGIN_H
#define LOGIN_H

#include "login_server.h"
#include "login_mode.h"
#include "login_new.h"
#include "login_join.h"
#include "../game/game_config.h"

#include <QWidget>
#include <QCloseEvent>

class Login : public QWidget {
private:
    LoginNew loginNew;
    LoginJoin loginJoin;
    LoginMode loginMode;
    LoginServer loginServer;
    bool & keepInput; 
public:
    Login(bool & keepInput, GameConfig & gameConfig, QWidget *parent = 0);
    
    virtual ~Login();
    
    void run();
    void stop();
    void quit();
    
    virtual void closeEvent(QCloseEvent *event);

};

#endif // LOGIN_H
