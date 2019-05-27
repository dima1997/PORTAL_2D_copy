//
// Created by franciscosicardi on 21/05/19.
//

#include "object_moves_event.h"
#include "protocol/protocol_code.h"

ObjectMovesEvent::ObjectMovesEvent(int objectId, float xPos, float yPos):
                                   Event(object_moves), objectId(objectId),
                                   xPos(xPos), yPos(yPos) {}

Connector &operator<<(Connector &out, const ObjectMovesEvent &event) {
    return out << (uint8_t) event.eventType << event.objectId << event.xPos << event.yPos;
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

Connector &operator>>(Connector &in, ObjectMovesEvent& e) {
    return in >> e.objectId >> e.xPos >> e.yPos;
}

ObjectMovesEvent::ObjectMovesEvent(): Event(object_moves), objectId(),
                                      xPos(), yPos() {}

ObjectMovesEvent::~ObjectMovesEvent() = default;
