#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include "../../includes/game/game.h"

#include <connector/connector.h>
#include <cstdint>

class GameConfig {
private:
    Connector connector;
    uint8_t gameId;
    uint32_t playerId;
    uint8_t mapId;

public:
    GameConfig();

    virtual ~GameConfig();

    void set_connector(Connector & connector);

    void set_game_id(uint8_t id);

    void set_player_id(uint32_t id);

    void set_map_id(uint8_t id);

    Game create_game();
};

#endif // GAME_CONFIG_H