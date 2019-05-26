//
// Created by franciscosicardi on 21/05/19.
//

#include "object_moves_event.h"
#include "protocol_code.h"

ObjectMovesEvent::ObjectMovesEvent(int objectId, float xPos, float yPos):
                                   Event(object_moves), objectId(objectId),
                                   xPos(xPos), yPos(yPos) {}

Connector &operator<<(Connector &out, const ObjectMovesEvent &event) {
    out << (uint8_t) event.eventType; 
    out << event.objectId << event.xPos << event.yPos;
    return out;
}

Connector &operator>>(Connector &out, ObjectMovesEvent &event) {
    out >> event.objectId;
    out >> event.xPos;
    out >> event.yPos;
    return out;
}

uint32_t ObjectMovesEvent::getId() const {
    return objectId;
}

float ObjectMovesEvent::getX() const {
    return xPos;
}

float ObjectMovesEvent::getY() const {
    return yPos;
}

ObjectMovesEvent::~ObjectMovesEvent() = default;
