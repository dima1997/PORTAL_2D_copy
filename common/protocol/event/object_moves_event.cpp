//
// Created by franciscosicardi on 21/05/19.
//

#include "object_moves_event.h"
#include "protocol/protocol_code.h"

ObjectMovesEvent::ObjectMovesEvent(int objectId, float xPos, float yPos):
                                   Event(object_moves), objectId(objectId),
                                   xPos(xPos), yPos(yPos) {}

ObjectMovesEvent::ObjectMovesEvent(
  int objectId, // por que es un int ?? y no un uint32_t
  float xPos, 
  float yPos, 
  EventType eventType
)
: Event(eventType), 
  objectId(objectId),
  xPos(xPos), 
  yPos(yPos) {}

uint32_t ObjectMovesEvent::getId() const {
    return objectId;
}

float ObjectMovesEvent::getX() const {
    return xPos;
}

float ObjectMovesEvent::getY() const {
    return yPos;
}

ObjectMovesEvent::ObjectMovesEvent(): Event(object_moves), objectId(),
                                      xPos(), yPos() {}

ObjectMovesEvent::~ObjectMovesEvent() = default;

/*
PRE: Recibe un conector (Connector &) conectado.
POST: Recibe el evento, desde el connector.
*/
void ObjectMovesEvent::receiveFrom(Connector & in){
    in >> this->objectId >> this->xPos >> this->yPos;
}
/*
PRE: Recibe un conector (Connector &) conectado.
POST: Envia el evento, a traves del connector.
*/
void ObjectMovesEvent::sendThrough(Connector & out) const{
    out << (uint8_t) this->eventType << this->objectId << this->xPos << this->yPos;
}
