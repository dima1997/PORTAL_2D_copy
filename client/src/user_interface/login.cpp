#include "../../includes/user_interface/login.h"

#include "ui_Login.h"

#include "../../includes/user_interface/login_new.h"
#include "../../includes/user_interface/login_join.h"

#include <connector/connector.h>

#include <QCloseEvent>
#include <iostream>

Login::Login(LoginEvent & loginEvent, 
          LoginNew & loginNew, 
          LoginJoin & loginJoin, 
          QWidget *parent)
:   QWidget(parent),
    loginEvent(loginEvent),
    loginNew(loginNew),
    loginJoin(loginJoin)
{
    this->loginEvent = NO_LOGIN;
    Ui::Login login;
    login.setupUi(this);
    this->loginNew.hide();
    this->loginJoin.hide();
    connectEvents();
}

Login::~Login() = default;


void Login::newGame() {
    // Simula recibir ids del connector
    this->loginJoin.close();
    std::vector<uint8_t> mapIds;
    for (uint8_t i = 0; i < 1; ++i){
        mapIds.push_back(i);
    }
    this->loginNew.setMapIds(mapIds);
    this->loginNew.show();
    this->loginEvent = NEW_LOGIN;
    this->close();
}

void Login::joinGame() {
    // Simula recibir ids del connector
    this->loginNew.close();
    std::vector<uint8_t> gameIds;
    for (uint8_t i = 1; i < 2; ++i){
        gameIds.push_back(i);
    }
    this->loginJoin.setGameIds(gameIds);
    this->loginJoin.show();
    this->loginEvent = JOIN_LOGIN;
    this->close();
}

void Login::connectEvents() {
    QPushButton* buttonNew = findChild<QPushButton*>("buttonNew");
    QObject::connect(buttonNew, &QPushButton::clicked,
                     this, &Login::newGame);

    QPushButton* buttonJoin = findChild<QPushButton*>("buttonJoin");
    QObject::connect(buttonJoin, &QPushButton::clicked,
                     this, &Login::joinGame);
}

/*
void Login::closeEvent(QCloseEvent *event){
    std::cout << "Atrape accion de cerrado, puedo cerrar sockets en dicho caso. ... :(\n";
    event->accept();
}
*/