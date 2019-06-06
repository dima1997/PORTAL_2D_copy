#include "../../includes/user_interface/login_new.h"

#include "ui_LoginNew.h"

#include <QWidget>

#include <cstdint>

LoginNew::LoginNew(bool & newed, uint8_t & mapId, QWidget *parent)
:   QWidget(parent),
    newed(newed),
    mapId(mapId) 
{
    this->newed = false;
    Ui::LoginNew loginNew;
    loginNew.setupUi(this);
    connectEvents();
}

LoginNew::~LoginNew() = default;

void LoginNew::newGame() {
    QComboBox* comboBoxMapId = findChild<QComboBox*>("comboBoxMapId");
    QString currentMapIdStr = comboBoxMapId->currentText();
    bool ok;
    int mapIdSelected = currentMapIdStr.toInt(&ok, 10);
    this->mapId = (uint8_t)mapIdSelected;
    this->newed = true;
    this->close();
}

void LoginNew::connectEvents() {
    QPushButton* buttonNew = findChild<QPushButton*>("buttonNew");
    QObject::connect(buttonNew, &QPushButton::clicked,
                     this, &LoginNew::newGame);
}

void LoginNew::setMapIds(std::vector<uint8_t> & mapIds){
    QComboBox* comboBoxMapId = findChild<QComboBox*>("comboBoxMapId");
    for (int i = 0; i < mapIds.size(); ++i){
        QString mapIdQStr = QString::number(mapIds[i]); 
        comboBoxMapId->addItem(mapIdQStr);
        
    }
}