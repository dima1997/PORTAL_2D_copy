#include "../../includes/user_interface/login_join.h"

#include "ui_LoginJoin.h"

#include <QWidget>

#include <cstdint>

LoginJoin::LoginJoin(bool & joined, uint8_t & gameId, QWidget *parent)
:   QWidget(parent),
    joined(joined),
    gameId(gameId)
{
    this->joined = false;
    Ui::LoginJoin loginJoin;
    loginJoin.setupUi(this);
    connectEvents();
}

LoginJoin::~LoginJoin() = default;

void LoginJoin::joinGame() {
    QComboBox* comboBoxGameId = findChild<QComboBox*>("comboBoxGameId");
    QString currentMapIdStr = comboBoxGameId->currentText();
    bool ok;
    int gameIdSelected = currentMapIdStr.toInt(&ok, 10);
    this->gameId = gameIdSelected;
    this->joined = true;
    this->close();
}

void LoginJoin::connectEvents() {
    QPushButton* buttonJoin = findChild<QPushButton*>("buttonJoin");
    QObject::connect(buttonJoin, &QPushButton::clicked,
                     this, &LoginJoin::joinGame);
}

void LoginJoin::setGameIds(std::vector<uint8_t> & gameIds){
    QComboBox* comboBoxGameId = findChild<QComboBox*>("comboBoxGameId");
    for (int i = 0; i < gameIds.size(); ++i){
        QString gameIdQStr = QString::number(gameIds[i]); 
        comboBoxGameId->addItem(gameIdQStr);
    }
}