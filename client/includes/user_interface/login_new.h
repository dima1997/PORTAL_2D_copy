#ifndef LOGIN_NEW_H
#define LOGIN_NEW_H

#include "../game/game_config.h"
#include <connector/connector.h>

#include <QWidget>

#include <cstdint>
#include <vector>

class LoginNew : public QWidget {
    Q_OBJECT
private:
    Connector connector;
    GameConfig & gameConfig;

    void config_new_game();
    void connect_events();

public:
    LoginNew(GameConfig & gameConfig, QWidget *parent = 0);
    virtual ~LoginNew();
    void set_connector(Connector & connector);
    void set_map_ids(std::vector<uint8_t> & mapIds);

signals:
    void login_new_success();
    void login_new_failed();
};

#endif // LOGIN_NEW_H