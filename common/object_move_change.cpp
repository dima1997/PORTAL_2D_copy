/*
#include "object_move_change.h"

#include "connector.h"

#include <cstdint>
*/
/*
PRE: Recibe el id de un objeto de juego donde se quiera 
realizar el cambio; y las nuevas coordenadas (float) x,y
del objeto antes mencionado.
POST: inicializa un cambio de ubicacion en un objeto del
juego.
*/
/*
ObjectMoveChange::ObjectMoveChange(uint32_t idGameObject, 
                                    float newX, float newY)
: idGameObject(idGameObject), newX(newX), newY(newY) {}
*/

/*Destruye el cambio de un objeto del juego.*/
//ObjectMoveChange::~ObjectMoveChange() = default;

/*
Contructor por copia.
PRE: Recibe una referencia constante a otro cambio de ubicacion 
de un objeto del juego (const ObjectMoveChange &).
POST: Inicializa un nuevo cambio de ubicacion de un objeto del 
juego, por copia.
*/
/*
ObjectMoveChange::ObjectMoveChange(const ObjectMoveChange & other)
: idGameObject(other.idGameObject), newX(other.newX), newY(other.newY) {}
*/
/*
Asignacion por copia.
PRE: Recibe una referencia constante a otro cambio de ubicacion 
de un objeto del juego (const ObjectMoveChange &).
POST: Asigna los atributos del cambio de ubicacion de un objeto del 
juego recibido, al actual.
Devuelve una referencia al cambio actual (ObjectMoveChange &).
*/
/*
ObjectMoveChange & ObjectMoveChange::operator=(const ObjectMoveChange & other){
    if (this == & other){
        return *this;
    }
    this->idGameObject = other.idGameObject;
    this->newX = other.newX;
    this->newY = other.newY;
}
*/
/*
PRE: Recibe un conector (Connector &).
POST: Se envia a traves del connector.
*/
/*
void ObjectMoveChange::sendThrough(Connector &out) const {
    const uint32_t idSend = this->idGameObject;
    const float xSend = this->newX;
    const float ySend = this->newY;
    out << idSend << xSend << ySend;
}
*/
/*
PRE: Recibe un conector (Connector &).
POST: Se recibe desde el conector.
*/
/*
void ObjectMoveChange::receiveFromm(Connector &out) {
    out >> this->idGameObject;
    out >> this->newX;
    out >> this->newY;
}
*/
/*
Devuelve el id (uint32_t) del objeto de juego 
donde se aplica el cambio.
*/
/*
uint32_t ObjectMoveChange::getId() const {
    return this->idGameObject;
}
*/
/*
Devuelve la nueva coordenada (float) X,
del objeto de juego referido.
*/
/*
float ObjectMoveChange::getX() const {
    return this->newX;
}
*/
/*
Devuelve la nueva coordenada (float) Y,
del objeto de juego referido.
*/
/*
float ObjectMoveChange::getY() const {
    return this->newY;
}
*/
