#ifndef PLAY_RESULT_H
#define PLAY_RESULT_H

#include <yaml-cpp/yaml.h>

enum PlayerStatus {
    ALIVE,
    DEAD
};

enum GameStatus {
    WON,
    LOST,
    NOT_FINISHED
};

class PlayResult {
private:
    GameStatus gameStatus;
    std::map<uint32_t,PlayerStatus> playersStatus;
public:
    /*
    PRE: Recibe el nodo base de YAML (YAML::Node) de
    la configutacion de juego actual.
    POST: Inicializa un resultado de juego.
    */
    PlayResult(YAML::Node & gameConfig);

    /*Destruye el estado del juego.*/
    ~PlayResult();

    /*
    Setea el status (PlayerStatus) del juegado 
    de id (uint32_t) recibido.
    */
    void setPlayerStatus(uint32_t id, PlayerStatus status);

    /*Setea el estado (GameStatus) del juego.*/
    void setGameStatus(GameStatus status);

    /*Imprime el resultado del juego por salida estandar.*/
    void print();
};

#endif // PLAY_RESULT_H