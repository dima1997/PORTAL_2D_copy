#ifndef LOGIN_NEW_H
#define LOGIN_NEW_H

#include "../game/game_config.h"
#include <connector/connector.h>

#include <QWidget>

#include <cstdint>

class LoginNew : public QWidget {
    Q_OBJECT
private:
    GameConfig & gameConfig;
    Connector connector;

    void newGame();
    void connectEvents();
    void setMapIds(std::vector<uint8_t> & mapIds);

public:
    LoginNew(GameConfig & gameConfig, QWidget *parent = 0);
    virtual ~LoginNew();
    void setConnector(Connector & connector);

signals:
    void login_new_success();
    void login_new_failed();
};

#endif // LOGIN_NEW_H