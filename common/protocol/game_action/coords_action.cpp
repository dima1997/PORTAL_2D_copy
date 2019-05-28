#include "coords_action.h"

#include <protocol/protocol_code.h>

/*
PRE: Recibe el nombre de una accion del juego (GameActionName); 
y unas coordenadas x,y (float).
POST: Inicializa un accion del juego con coordenadas.
*/
CoordsAction::CoordsAction(GameActionName gameActionName, 
float xCoord, float yCoord)
:   GameAction(gameActionName), xCoord(xCoord), yCoord(yCoord) {}

/*
PRE: Recibe el nombre de un accion del juego (GameActionName).
POST: Inicializa una accion del juego con dicho nombre y 
coordenadas nulas (0,0).
*/
CoordsAction::CoordsAction(GameActionName gameActionName)
:   GameAction(gameActionName), xCoord(0), yCoord(0) {}

/*Destruye una accion del juego con coordenadas.*/
CoordsAction::~CoordsAction() = default;

/*
PRE: Recibe un conector (Connector &).
POST: La accion se envia a traves del conector.
*/
void CoordsAction::sendThrough(Connector &out) const {
    auto gameActionNameExplicit = (uint8_t) this->gameActionName;
    out << gameActionNameExplicit;
    out << this->xCoord;
    out << this->yCoord;
}

/*
PRE: Recibe un conector (Connector &).
POST: La accion se recibe desde el conector.
*/
void CoordsAction::receiveFrom(Connector &out) {
    // ESTAS DOS PRIMERAS LINEAS PUEDEN RETIRARSE O AGREGARSE SEGUN 
    //RESULTE CONVENIENTE. Y RECIBIR/NO RECIBIR DESDE AFUERA.
    /*
    uint8_t gameActionNameExplicit;
    out >> gameActionNameExplicit;
    this->gameActionName = (GameActionName) gameActionNameExplicit;
    */
    // ----------------------------------------------------------------
    out >> this->xCoord;
    out >> this->yCoord;
}

/*Devuelve la coordenada x (float) de la accion con coordenadas.*/
float CoordsAction::getX(){
    return this->xCoord;
}

/*Devuelve la coordenada y (float) de la accion con coordenadas.*/
float CoordsAction::getY(){
    return this->yCoord;
}

