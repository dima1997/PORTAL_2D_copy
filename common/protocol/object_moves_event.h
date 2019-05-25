//
// Created by franciscosicardi on 21/05/19.
//

#ifndef PORTAL_OBJECT_MOVES_EVENT_H
#define PORTAL_OBJECT_MOVES_EVENT_H


#include "event.h"
#include "../connector/connector.h"

class ObjectMovesEvent: public Event {
public:
    uint32_t objectId;
    float xPos;
    float yPos;
    ObjectMovesEvent(int objectId, float xPos, float yPos);
    ~ObjectMovesEvent() override;
    friend Connector &operator<<(Connector &out, const ObjectMovesEvent &c);
};


#endif //PORTAL_OBJECT_MOVES_EVENT_H
