//
// Created by franciscosicardi on 21/05/19.
//

#include "object_moves_event.h"
#include "protocol_code.h"

ObjectMovesEvent::ObjectMovesEvent(int objectId, float xPos, float yPos):
                                   Event(object_moves), objectId(objectId),
                                   xPos(xPos), yPos(yPos) {}

Connector &operator<<(Connector &out, const ObjectMovesEvent &event) {
    // TODO: fix float serialization
    out << event.eventType << event.objectId << event.xPos << event.yPos;
    return out;
}

ObjectMovesEvent::~ObjectMovesEvent() = default;
