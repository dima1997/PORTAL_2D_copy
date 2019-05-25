#include "game_action.h"

#include "connector.h"
#include "protocol_code.h"

/*
PRE: Recibe el nombre de una accion del juego (GameActionName).
POST: Inicializa un accion del juego.
*/
GameAction::GameAction(GameActionName gameActionName)
: gameActionName(gameActionName) {}

/*Destruye una accion del juego.*/
GameAction::~GameAction() = default;

/*
PRE: Recibe una referencia constante a otra accion del juego
(const GameAction %).
POST: Crea una nueva accion del juego por copia.
*/
GameAction::GameAction(const GameAction & other)
: gameActionName(other.gameActionName) {}

/*
PRE: Recibe una referencia constante a otra accion del juego
(const GameAction %).
POST: Asigna los atributos de la accion recibida a la actual.
Devuelve una referencia a la acccion actual.
*/
GameAction & GameAction::operator=(const GameAction & other){
    if (this == &other){
        return *this;
    }
    this->gameActionName = other.gameActionName;
    return *this;
}

/*
PRE: Recibe un conector (Connector &).
POST: La accion se envia a traves del conector.
*/
void GameAction::sendThrough(Connector &out) const{
    uint8_t gameActionNameExplicit = (uint8_t) this->gameActionName;
    out << gameActionNameExplicit;
}

/*
PRE: Recibe un conector (Connector &).
POST: La accion se recibe desde el conector.
*/
void GameAction::receiveFrom(Connector &out){
    uint8_t gameActionNameExplicit;
    out >> gameActionNameExplicit;
    this->gameActionName = (GameActionName) gameActionNameExplicit;
}

/*
PRE: Recibe un conector (Connector &), y una referencia 
constante a una accion del juego (const GameAction &).
POST: Envia la accion del juego a traves del conector.
*/
Connector & operator<<(Connector &out, const GameAction &action){
    action.sendThrough(out);
    return out;
}

/*
PRE: Recibe un conector (Connector &), y una accion del 
juego (GameAction &).
POST: Recibe la accion del juego a traves del conector.
La accion de juego recibida es modificada.
*/
Connector & operator>>(Connector &out, GameAction &action){
    action.receiveFrom(out);
    return out;
}
