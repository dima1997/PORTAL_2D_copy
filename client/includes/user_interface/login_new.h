#ifndef LOGIN_NEW_H
#define LOGIN_NEW_H

#include "../game/game_config.h"
#include <connector/connector.h>

#include <QWidget>
#include <QCloseEvent>

#include <cstdint>
#include <vector>

class LoginNew : public QWidget {
//    Q_OBJECT
private:
    Connector connector;
    GameConfig & gameConfig;
    bool isOpen;

    void config_new_game();
    void connect_events();

public:
    LoginNew(GameConfig & gameConfig, QWidget *parent = 0);
    virtual ~LoginNew();
    void set_connector(Connector & connector);
    void set_map_ids(std::vector<uint8_t> & mapIds);
    virtual void closeEvent(QCloseEvent *event);
    void quit();
/*
signals:
    void login_new_success();
    void login_new_failed();
*/
};

#endif // LOGIN_NEW_H