#include "../../includes/user_interface/login_new.h"

#include "../../includes/user_interface/login.h"
#include "../../includes/game/game_config.h"

#include "ui_LoginNew.h"

#include <QWidget>
#include <QMessageBox>
#include <QLineEdit>

#include <cstdint>
#include <sstream>
#include <iostream>

LoginNew::LoginNew(GameConfig & gameConfig, QWidget *parent)
:   QWidget(parent),
    gameConfig(gameConfig),
    connector(),
    isOpen(true)
{
    Ui::LoginNew loginNew;
    loginNew.setupUi(this);
    this->hide();
    this->connect_events();
}

LoginNew::~LoginNew() = default;

void LoginNew::config_new_game() {
    this->hide();
    QComboBox* comboBoxMapId = findChild<QComboBox*>("comboBoxMapId");
    QString currentMapIdStr = comboBoxMapId->currentText();
    bool allOk;
    uint8_t mapId = (uint8_t) currentMapIdStr.toInt(&allOk, 10);
    QLineEdit* lineGameName = findChild<QLineEdit*>("lineGameName");
    QString gameNameQStr = lineGameName->text();
    std::string gameName = gameNameQStr.toUtf8().constData();
    this->connector << (uint8_t) mapId;
    this->connector << gameName;
    uint8_t status;
    this->connector >> status;
    if (status != command_ok){
        QMessageBox qMsg;
        qMsg.setWindowTitle("Portal");
        std::stringstream err;
        err << "Server rejected new game.\n";
        qMsg.setText(QString(err.str().c_str()));
        qMsg.exec();
        ((Login*)this->parentWidget())->close();
        this->close();
        return;
    }
    uint8_t gameId;
    this->connector >> gameId;
    uint32_t playerId;
    this->connector >> playerId;
    std::string mapYaml;
    connector >> mapYaml;
    /*
    uint8_t start;
    std::cout << "Waiting for other players at QT ... \n";
    connector >> start;
    */
    this->gameConfig.set_connector(this->connector);
    this->gameConfig.set_game_id(gameId);
    this->gameConfig.set_player_id(playerId);
    this->gameConfig.set_map(mapYaml);
    this->gameConfig.set_well_config();
    QMessageBox qMsg;
    qMsg.setWindowTitle("Portal");
    std::stringstream ok;
    ok << "New game success.\n";
    qMsg.setText(QString(ok.str().c_str()));
    qMsg.exec();
    ((Login*)this->parentWidget())->close();
    this->close();
    return;
}

void LoginNew::quit(){
    ((Login*)this->parentWidget())->quit();
    this->close();
}

void LoginNew::connect_events() {
    QPushButton* buttonNew = findChild<QPushButton*>("buttonNew");
    QObject::connect(buttonNew, &QPushButton::clicked,
                     this, &LoginNew::config_new_game);
    
    QPushButton* buttonQuit = findChild<QPushButton*>("buttonQuit");
    QObject::connect(buttonQuit, &QPushButton::clicked,
                     this, &LoginNew::quit);
}

void LoginNew::set_map_ids(std::vector<uint8_t> & mapIds){
    QComboBox* comboBoxMapId = findChild<QComboBox*>("comboBoxMapId");
    for (int i = 0; i < (int)mapIds.size(); ++i){
        QString mapIdQStr = QString::number(mapIds[i]); 
        comboBoxMapId->addItem(mapIdQStr);
    }
}

void LoginNew::set_connector(Connector & connector){
    this->connector = std::move(connector);
}

void LoginNew::closeEvent(QCloseEvent *event){
    if (! this->isOpen){
        return;
    }
    try {
        this->connector.shutDownRD();
        this->connector.shutDownWR();
    } catch (SocketException &error){}
        event->accept();    
}