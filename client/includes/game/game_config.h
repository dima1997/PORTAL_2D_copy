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
    std::string mapYaml;
    bool isWellConfig;

public:
    GameConfig();

    /*
    Inicializa una configuracion de 
    juego sin setear correcta.
    */
    GameConfig(
        Connector & connector,
        uint8_t gameId,
        uint32_t playerId,
        const std::string & mapYaml
    );

    virtual ~GameConfig();

    GameConfig(GameConfig && other);

    GameConfig & operator=(GameConfig && other);

    void set_connector(Connector & connector);

    void set_game_id(uint8_t id);

    void set_player_id(uint32_t id);

    void set_map(const std::string & mapYaml);

    void set_well_config();

    bool is_well_config();

    Game create_game();
};

#endif // GAME_CONFIG_H