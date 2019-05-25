//#include "object_move_change.h"
//
//#include <cstdint>
//
///*
//PRE: Recibe el id de un objeto de juego donde se quiera
//realizar el cambio; y las nuevas coordenadas (float) x,y
//del objeto antes mencionado.
//POST: inicializa un cambio de ubicacion en un objeto del
//juego.
//*/
//ObjectMoveChange::ObjectMoveChange(uint32_t idGameObject,
//                                    float newX, float newY)
//: idGameObject(idGameObject), newX(newX), newY(newY) {}
//
///*Destruye el cambio de un objeto del juego.*/
//ObjectMoveChange::~ObjectMoveChange() = default;
//
///*
//Devuelve el id (uint32_t) del objeto de juego
//donde se aplica el cambio.
//*/
//uint32_t ObjectMoveChange::getId() const {
//    return this->idGameObject;
//}
//
///*
//Devuelve la nueva coordenada (float) X,
//del objeto de juego referido.
//*/
//float ObjectMoveChange::getX() const {
//    return this->newX;
//}
//
///*
//Devuelve la nueva coordenada (float) Y,
//del objeto de juego referido.
//*/
//float ObjectMoveChange::getY() const {
//    return this->newY;
//}
