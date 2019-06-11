#include "../../includes/user_interface/login_mode.h"

#include "ui_LoginMode.h"

#include "../../includes/user_interface/login_new.h"
#include "../../includes/user_interface/login_join.h"

#include <connector/connector.h>

#include <sstream>

LoginMode::LoginMode( 
    LoginNew & loginNew, 
    LoginJoin & loginJoin, 
    QWidget *parent)
:   QWidget(parent),
    loginNew(loginNew),
    loginJoin(loginJoin),
    connector()
{
    this->hide();
    Ui::LoginMode loginMode;
    loginMode.setupUi(this);
    this->connectEvents();
}

LoginMode::~LoginMode() = default;

/*
PRE: Recibe un connector (Connector &).
POST: Toma posesion del connector por movimiento. 
*/
void LoginMode::setConnector(Connector & connector){
    this->connector = std::move(connector);
}

void LoginMode::newGame() {
    this->loginJoin.close();
    this->connector << (uint8_t) new_game;
    // Simula recibir ids del connector
    std::vector<uint8_t> mapIds;
    for (uint8_t i = 0; i < 1; ++i){
        mapIds.push_back(i);
    }
    this->loginNew.setConnector(this->connector);
    this->loginNew.setMapIds(mapIds);
    this->close();
    emit login_mode_new();
    return;
}

void LoginMode::joinGame() {
    this->loginNew.close();

    this->connector << (uint8_t) join_game;
    uint8_t gameCount;
    this->connector >> gameCount;
    if (gameCount == 0){
        QMessageBox msg;
        msg.setWindowTitle("PORTAL");
        std::stringstream err;
        err << "No games in stock.\n"; 
        qMsg.setText(QString(err.str.c_str()));
        qMsg.setIcon(QMessageBox::Warning);
        qMsg.exec();
        this->close();
        emit login_mode_failed();
        return;
    }
    std::map<uint8_t,std::string> stockGames;
    for (uint8_t i = 0; i < gameCount; ++i) {
        uint8_t gameId;
        this->connector >> gameId;
        std::string gameName;
        this->connector >> gameName;
        std::pair<uint8_t,std::string> oneGame(gameId, gameName);
        stockGames.insert(oneGame);
    }
    this->loginJoin.setConnector(this->connector);
    this->loginJoin.setGameIds(gameIds);
    this->close();
    emit login_mode_join();
    return;
}

void LoginMode::connectEvents() {
    QPushButton* buttonNew = findChild<QPushButton*>("buttonNew");
    QObject::connect(buttonNew, &QPushButton::clicked,
                     this, &Login::newGame);

    QPushButton* buttonJoin = findChild<QPushButton*>("buttonJoin");
    QObject::connect(buttonJoin, &QPushButton::clicked,
                     this, &Login::joinGame);
}