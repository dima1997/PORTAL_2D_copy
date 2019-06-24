#ifndef LOGIN_JOIN_H
#define LOGIN_JOIN_H

#include <connector/connector.h>

#include <QWidget>
#include <QCloseEvent>

#include <cstdint>
#include <map>

class GameConfig;

class LoginJoin : public QWidget {
private:
    Connector connector;
    GameConfig & gameConfig;
    std::map<std::string,uint8_t> gameIds;
    bool isOpen;
    
    void connect_events();
    void config_join_game();
public:
    LoginJoin(GameConfig & gameConfig, QWidget *parent = 0);
    virtual ~LoginJoin();
    void set_game_ids(std::map<uint8_t,std::string> & stockGames);
    void set_connector(Connector & connector);
    virtual void closeEvent(QCloseEvent *event);
    void quit();
};

#endif // LOGIN_JOIN_H
