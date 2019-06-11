#ifndef LOGIN_JOIN_H
#define LOGIN_JOIN_H

#include "../game/game_config.h"
#include <connector/connector.h>

#include <QWidget>

#include <cstdint>
#include <map>

class LoginJoin : public QWidget {
    Q_OBJECT
private:
    Connector connector;
    GameConfig & gameConfig;

    void connect_events();
    void config_join_game();
public:
    LoginJoin(GameConfig & gameConfig, QWidget *parent = );
    virtual ~LoginJoin();
    void set_game_ids(std::map<uint8_t,std::string> & stockGames);
    void set_connector(Connector & connector);

signals:
    void login_join_success();
    void login_join_failed();
};

#endif // LOGIN_JOIN_H
