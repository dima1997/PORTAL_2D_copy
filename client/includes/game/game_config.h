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
    /*
    Inicia una configuracion de 
    juego nula.
    */
    GameConfig();

    /*
    Inicializa una configuracion de 
    juego bien configurada.
    */
    GameConfig(
        Connector & connector,
        uint8_t gameId,
        uint32_t playerId,
        const std::string & mapYaml
    );

    /*Destructor.*/
    virtual ~GameConfig();

    /*Constructor por movimiento.*/
    GameConfig(GameConfig && other);

    /*Asignacion por movimiento.*/
    GameConfig & operator=(GameConfig && other);

    /*
    PRE: Recibe un connector.
    POST: Se apodera por movimiento del connector.
    */
    void set_connector(Connector & connector);

    /*Setea el id del juego.*/
    void set_game_id(uint8_t id);

    /*Setea el id del jugador principal.*/
    void set_player_id(uint32_t id);

    /*Setea el mapa de juego.*/
    void set_map(const std::string & mapYaml);

    /*
    Establece bien configurada, 
    la configuracion.
    */
    void set_well_config();

    /*
    Devuelve true si la configuracion es 
    correcta; false en caso contrario
    */
    bool is_well_config();

    /*
    Devuelve un juego bajo la 
    configuracion actual
    */
    Game create_game();
};

#endif // GAME_CONFIG_H