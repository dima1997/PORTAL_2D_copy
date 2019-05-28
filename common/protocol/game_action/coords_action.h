#ifndef COORDS_ACTION_H
#define COORDS_ACTION_H

#include <protocol/game_action/game_action.h>
#include <protocol/protocol_code.h>
#include <connector/connector.h>

class CoordsAction : public GameAction {
private:
    float xCoord;
    float yCoord;
public:
    /*
    PRE: Recibe el nombre de una accion del juego (GameActionName); 
    y unas coordenadas x,y (float).
    POST: Inicializa un accion del juego con coordenadas.
    */
    explicit CoordsAction(GameActionName gameActionName, 
        float xCoord, float yCoord);

    /*
    PRE: Recibe el nombre de un accion del juego (GameActionName).
    POST: Inicializa una accion del juego con dicho nombre y 
    coordenadas nulas (0,0).
    */
    CoordsAction(GameActionName gameActionName);

    /*Destruye una accion del juego con coordenadas.*/
    virtual ~CoordsAction();

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

    /*Devuelve la coordenada x (float) de la accion con coordenadas.*/
    float getX();

    /*Devuelve la coordenada y (float) de la accion con coordenadas.*/
    float getY();
};

#endif // COORDS_ACTION_H
