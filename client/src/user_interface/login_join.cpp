#include "../../includes/user_interface/login_join.h"

#include "ui_LoginJoin.h"

#include "../game/game_config.h"

#include <connector/connector.h>

#include <QWidget>

#include <cstdint>
#include <map>

LoginJoin::LoginJoin(GameConfig & gameConfig, QWidget *parent)
:   QWidget(parent),
    gameConfig(gameConfig),
    connector()
{
    this->hide();
    Ui::LoginJoin loginJoin;
    loginJoin.setupUi(this);
    this->connectEvents();
}

LoginJoin::~LoginJoin() = default;

void LoginJoin::joinGame() {
    QComboBox* comboBoxGameId = findChild<QComboBox*>("comboBoxGameId");
    QString currentMapIdStr = comboBoxGameId->currentText();
    bool ok;
    uint8_t gameId = (uint8_t) currentMapIdStr.toInt(&ok, 10);
    this->connector << (uint8_t) gameId;
    uint8_t status;
    this->connector >> status;
    if (status == command_ok){
        uint32_t playerId;
        this->connector >> playerId;
        //Pedir mapa
        uint8_t mapId = 0;
        this->gameConfig.set_connector(this->connector);
        this->gameConfig.set_game_id(gameId);
        this->gameConfig.set_player_id(playerId);
        this->gameConfig.set_map_id(mapId);
        QMessageBox qMsg;
        qMsg.setWindowTitle("Portal");
        std::stringstream ok;
        ok << "Join game success.\n";
        qMsg.setText(QString(ok.str.c_str()));
        qMsg.exec();
        this->close();
        emit login_join_success();
        return;
    }
    if (status == game_is_full) {
        QMessageBox qMsg;
        qMsg.setWindowTitle("Portal");
        std::stringstream err;
        err << "Game " << (unsigned) gameId << " is full." << std::endl;
        qMsg.setText(QString(err.str.c_str()));
        qMsg.exec();
        this->close();
        emit login_join_failed();
        return;
    } 
    if (status == non_existent_game) {
        QMessageBox qMsg;
        qMsg.setWindowTitle("Portal");
        std::stringstream err;
        err << "Game " << (unsigned) gameId << " does not exist." << std::endl;
        qMsg.setText(QString(err.str.c_str()));
        qMsg.exec();
        this->close();
        emit login_join_failed();
        return;
    }
}

void LoginJoin::connect_events() {
    QPushButton* buttonJoin = findChild<QPushButton*>("buttonJoin");
    QObject::connect(buttonJoin, &QPushButton::clicked,
                     this, &LoginJoin::joinGame);
}

void LoginJoin::set_game_ids(std::map<uint8_t,std::string> & stockGames){
    QComboBox* comboBoxGameId = findChild<QComboBox*>("comboBoxGameId");
    for (std::map<uint8_t,std::string>::iterator it=stockGames.begin(); 
        it!=stockGames.end(); ++it){
        uint8_t gameId = it->first;
        std::string gameName = it->second;
        std::stringstream oneGame;
        oneGame << (unsigned) gameId << " - " << gameName;
        this->gamesId.insert(std::make_pair<std::string, uint8_t>(
            oneGame.str(),gameId
        ));
        comboBoxGameId->addItem(QString(oneGame.str().c_str()));
    }
}

void LoginJoin::set_connector(Connector & connector){
    this->connector = std::move(connector);
}