#include "../../includes/user_interface/login_join.h"

#include "ui_LoginJoin.h"

#include "../../includes/user_interface/login.h"
#include "../../includes/game/game_config.h"

#include <connector/connector.h>

#include <QWidget>
#include <QMessageBox>

#include <cstdint>
#include <map>
#include <sstream>

LoginJoin::LoginJoin(GameConfig & gameConfig, QWidget *parent)
:   QWidget(parent),
    gameConfig(gameConfig),
    connector(),
    gameIds(),
    isOpen(true)
{
    Ui::LoginJoin loginJoin;
    loginJoin.setupUi(this);
    this->hide();
    this->connect_events();
}

LoginJoin::~LoginJoin() = default;

void LoginJoin::config_join_game() {
    QComboBox* comboBoxGameId = findChild<QComboBox*>("comboBoxGameId");
    QString currentMapIdNameStr = comboBoxGameId->currentText();
    QStringList pieces = currentMapIdNameStr.split(" - ");
    QString currentMapIdStr = pieces[0]; 
    bool ok;
    uint8_t gameId = (uint8_t) currentMapIdStr.toInt(&ok, 10);
    this->connector << (uint8_t) gameId;
    uint8_t status;
    this->connector >> status;
    if (status == command_ok){
        uint32_t playerId;
        this->connector >> playerId;
        uint8_t mapId = 0; // Esto es irrelevante
        this->gameConfig.set_connector(this->connector);
        this->gameConfig.set_game_id(gameId);
        this->gameConfig.set_player_id(playerId);
        this->gameConfig.set_map_id(mapId);
        this->gameConfig.set_well_config();
        QMessageBox qMsg;
        qMsg.setWindowTitle("Portal");
        std::stringstream ok;
        ok << "Join game success.\n";
        qMsg.setText(QString(ok.str().c_str()));
        qMsg.exec();
        ((Login*)this->parentWidget())->close();
        this->close();
        return;
    }
    if (status == game_is_full) {
        QMessageBox qMsg;
        qMsg.setWindowTitle("Portal");
        std::stringstream err;
        err << "Game " << (unsigned) gameId << " is full." << std::endl;
        qMsg.setText(QString(err.str().c_str()));
        qMsg.exec();
        ((Login*)this->parentWidget())->close();
        this->close();
        return;
    } 
    if (status == non_existent_game) {
        QMessageBox qMsg;
        qMsg.setWindowTitle("Portal");
        std::stringstream err;
        err << "Game " << (unsigned) gameId << " does not exist." << std::endl;
        qMsg.setText(QString(err.str().c_str()));
        qMsg.exec();
        ((Login*)this->parentWidget())->close();
        this->close();
        return;
    }
}

void LoginJoin::connect_events() {
    QPushButton* buttonJoin = findChild<QPushButton*>("buttonJoin");
    QObject::connect(buttonJoin, &QPushButton::clicked,
                     this, &LoginJoin::config_join_game);
    
    QPushButton* buttonQuit = findChild<QPushButton*>("buttonQuit");
    QObject::connect(buttonQuit, &QPushButton::clicked,
                     this, &LoginJoin::quit);
}

void LoginJoin::set_game_ids(std::map<uint8_t,std::string> & stockGames){
    QComboBox* comboBoxGameId = findChild<QComboBox*>("comboBoxGameId");
    for (std::map<uint8_t,std::string>::iterator it=stockGames.begin(); 
        it!=stockGames.end(); ++it){
        uint8_t gameId = it->first;
        std::string gameName = it->second;
        std::stringstream oneGame;
        oneGame << (unsigned) gameId << " - " << gameName;
        std::string oneGameStr = oneGame.str();
        this->gameIds.insert(std::pair<std::string, uint8_t>(
            oneGameStr,gameId
        ));
        comboBoxGameId->addItem(QString(oneGameStr.c_str()));
    }
}

void LoginJoin::set_connector(Connector & connector){
    this->connector = std::move(connector);
}

void LoginJoin::closeEvent(QCloseEvent *event){
    if (! this->isOpen){
        return;
    }
    try {
        this->connector.shutDownRD();
        this->connector.shutDownWR();
    } catch (SocketException &error){}
        event->accept();    
}

void LoginJoin::quit(){
    ((Login*)this->parentWidget())->quit();
    this->close();
}