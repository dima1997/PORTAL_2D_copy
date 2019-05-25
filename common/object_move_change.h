/*
#ifndef OBJECT_MOVE_CHANGE_H
#define OBJECT_MOVE_CHANGE_H

#include "connector.h"

#include <cstdint>

class ObjectMoveChange {
private:
    uint32_t idGameObject;
    float newX;
    float newY;
*/    
//public:
    /*
    PRE: Recibe el id de un objeto de juego donde se quiera 
    realizar el cambio; y las nuevas coordenadas (float) x,y
    del objeto antes mencionado.
    POST: inicializa un cambio de ubicacion en un objeto del
    juego.
    */
    //ObjectMoveChange(uint32_t idGameObject, float newX, float newY);

    /*Destruye el cambio de un objeto del juego.*/
    //~ObjectMoveChange();

    /*
    Contructor por copia.
    PRE: Recibe una referencia constante a otro cambio de ubicacion 
    de un objeto del juego (const ObjectMoveChange &).
    POST: Inicializa un nuevo cambio de ubicacion de un objeto del 
    juego, por copia.
    */
    //ObjectMoveChange(const ObjectMoveChange & other);

    /*
    Asignacion por copia.
    PRE: Recibe una referencia constante a otro cambio de ubicacion 
    de un objeto del juego (const ObjectMoveChange &).
    POST: Asigna los atributos del cambio de ubicacion de un objeto del 
    juego recibido, al actual.
    Devuelve una referencia al cambio actual (ObjectMoveChange &).
    */
    //ObjectMoveChange & operator=(const ObjectMoveChange & other);

    /*
    PRE: Recibe un conector (Connector &).
    POST: Se envia a traves del connector.
    */
    //virtual void sendThrough(Connector &out) const;

    /*
    PRE: Recibe un conector (Connector &).
    POST: Se recibe desde el conector.
    */
    //virtual void receiveFromm(Connector &out);

    /*
    Devuelve el id (uint32_t) del objeto de juego 
    donde se aplica el cambio.
    */
    //uint32_t getId() const;

    /*
    Devuelve la nueva coordenada (float) X,
    del objeto de juego referido.
    */
    //float getX() const;

    /*
    Devuelve la nueva coordenada (float) Y,
    del objeto de juego referido.
    */
    //float getY() const;

    /*
    PRE: Recibe un conector (Connector &), y una referencia 
    constante a una cambio de ubicacion de un objeto del juego 
    (const ObjectMoveChange &).
    POST: Envia el cambio a traves del conector.
    */
    //friend Connector &operator<<(Connector &out, const ObjectMoveChange & change);

    /*
    PRE: Recibe un conector (Connector &), y una referencia 
    una cambio de ubicacion de un objeto del juego 
    (const ObjectMoveChange &).
    POST: Recibe el cambio a traves del conector, lo guarda el 
    cambio recibido.
    */
    //friend Connector &operator>>(Connector &out, ObjectMoveChange & change);
//};

//#endif // OBJECT_MOVE_CHANGE_H
