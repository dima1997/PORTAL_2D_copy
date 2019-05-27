#ifndef GAME_ACTION_H
#define GAME_ACTION_H

#include <connector/connector.h>
#include <protocol/protocol_code.h>

#include <cstdint>

class GameAction {
protected:
    GameActionName gameActionName;
    uint32_t playerId;
public:
    /*
    PRE: Recibe el nombre de una accion del juego (GameActionName).
    POST: Inicializa un accion del juego.
    */
    explicit GameAction(GameActionName gameActionName);

    GameAction();

    /*Destruye una accion del juego.*/
    virtual ~GameAction();

    /*
    PRE: Recibe una referencia constante a otra accion del juego
    (const GameAction %).
    POST: Crea una nueva accion del juego por copia.
    */
    GameAction(const GameAction & other);
    /*
    PRE: Recibe una referencia constante a otra accion del juego
    (const GameAction %).
    POST: Asigna los atributos de la accion recibida a la actual.
    Devuelve una referencia a la acccion actual.
    */
    GameAction & operator=(const GameAction & other);

    /*
    PRE: Recibe un conector (Connector &).
    POST: La accion se envia a traves del conector.
    */
    virtual void sendThrough(Connector &out) const;
    
    /*
    PRE: Recibe un conector (Connector &).
    POST: La accion se recibe desde el conector.
    */
    virtual void receiveFrom(Connector &out);
    
    /*
    PRE: Recibe un conector (Connector &), y y una referencia 
    constante a una accion del juego (const GameAction &).
    POST: Envia la accion del juego a traves del conector.
    */
    friend Connector &operator<<(Connector &out, const GameAction &action);
    
    /*
    PRE: Recibe un conector (Connector &), y una accion del 
    juego (GameAction &).
    POST: Recibe la accion del juego a traves del conector.
    La accion de juego recibida es modificada.
    */
    friend Connector &operator>>(Connector &out, GameAction &action);

    GameActionName getGameActionName();

    void setPlayerId(uint32_t id);

    uint8_t getPlayerId();
};

#endif // GAME_ACTION_H
