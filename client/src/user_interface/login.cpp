#include "../../includes/user_interface/login.h"

#include "ui_Login.h"

#include "../../includes/game/game_config.h"

#include "../../includes/user_interface/login_server.h"
#include "../../includes/user_interface/login_mode.h"
#include "../../includes/user_interface/login_new.h"
#include "../../includes/user_interface/login_join.h"
#include "../../includes/game/game_config.h"

#include <QWidget>
#include <QCloseEvent>

Login::Login(bool & keepInput, GameConfig & gameConfig, QWidget *parent)
:   loginNew(gameConfig, this),
    loginJoin(gameConfig, this),
    loginMode(this->loginNew, this->loginJoin, this),
    loginServer(this->loginMode, this),
    keepInput(keepInput)   
{
    this->hide();
    Ui::Login login;
    login.setupUi(this);
    this->keepInput = true;
}

Login::~Login() = default;

void Login::run(){
    this->show();
    this->loginServer.show();
}

void Login::stop(){
    this->loginServer.close();
    this->loginMode.close();
    this->loginNew.close();
    this->loginJoin.close();
}

void Login::closeEvent(QCloseEvent *event){
    this->stop();
    event->accept();
}

void Login::quit(){
    this->keepInput = false;
    this->close();
}