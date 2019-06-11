#include "../../includes/user_interface/login_mode.h"

#include "ui_LoginMode.h"

#include "../../includes/user_interface/login_new.h"
#include "../../includes/user_interface/login_join.h"

#include <connector/connector.h>

#include <QWidget>
#include <QMessageBox>

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
    this->connect_events();
}

LoginMode::~LoginMode() = default;

/*
PRE: Recibe un connector (Connector &).
POST: Toma posesion del connector por movimiento. 
*/
void LoginMode::set_connector(Connector & connector){
    this->connector = std::move(connector);
}

void LoginMode::config_new_game() {
    this->loginJoin.close();
    this->connector << (uint8_t) new_game;
    // Simula recibir ids del connector
    std::vector<uint8_t> mapIds;
    for (uint8_t i = 0; i < 1; ++i){
        mapIds.push_back(i);
    }
    this->loginNew.set_connector(this->connector);
    this->loginNew.set_map_ids(mapIds);
    this->close();
    emit login_mode_new();
    return;
}

void LoginMode::config_join_game() {
    this->loginNew.close();

    this->connector << (uint8_t) join_game;
    uint8_t gameCount;
    this->connector >> gameCount;
    if (gameCount == 0){
        QMessageBox qMsg;
        qMsg.setWindowTitle("PORTAL");
        std::stringstream err;
        err << "No games in stock.\n"; 
        qMsg.setText(QString(err.str().c_str()));
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
    this->loginJoin.set_connector(this->connector);
    this->loginJoin.set_game_ids(stockGames);
    this->close();
    emit login_mode_join();
    return;
}

void LoginMode::connect_events() {
    QPushButton* buttonNew = findChild<QPushButton*>("buttonNew");
    QObject::connect(buttonNew, &QPushButton::clicked,
                     this, &LoginMode::config_new_game);

    QPushButton* buttonJoin = findChild<QPushButton*>("buttonJoin");
    QObject::connect(buttonJoin, &QPushButton::clicked,
                     this, &LoginMode::config_join_game);
}