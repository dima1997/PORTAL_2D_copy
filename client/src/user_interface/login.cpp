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
#include <QDesktopWidget>
#include <QPixmap>

#define PATH_BACKGROUND "/home/soporte/Documentos/Fiuba/cuatrimestre_actual/a_taller_1/tp_final/rama_master/TP4_TALLER/client/assets/portal_background_4.jpg"
#define LOGIN_WIDTH 640
#define LOGIN_HEIGHT 480

Login::Login(bool & keepInput, GameConfig & gameConfig, QWidget *parent)
:   loginNew(gameConfig, this),
    loginJoin(gameConfig, this),
    loginMode(this->loginNew, this->loginJoin, this),
    loginServer(this->loginMode, this),
    keepInput(keepInput)   
{
    Ui::Login login;
    login.setupUi(this);
    this->hide();
    this->setFixedSize(LOGIN_WIDTH,LOGIN_HEIGHT);
    this->loginServer.setFixedSize(LOGIN_WIDTH,LOGIN_HEIGHT);
    this->loginMode.setFixedSize(LOGIN_WIDTH,LOGIN_HEIGHT);
    this->loginNew.setFixedSize(LOGIN_WIDTH,LOGIN_HEIGHT);
    this->loginJoin.setFixedSize(LOGIN_WIDTH,LOGIN_HEIGHT);
    this->adjustSize();
    this->move(
        QApplication::desktop()->screen()->rect().center() 
        - (this->rect()).center()
    );
    QPixmap bkgnd(PATH_BACKGROUND);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    this->keepInput = true;
}

Login::~Login() = default;

void Login::run(){
    this->show();
    this->loginServer.show();
    this->adjustSize();
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