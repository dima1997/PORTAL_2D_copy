//
// Created by franciscosicardi on 21/05/19.
//

#ifndef PORTAL_OBJECT_MOVES_EVENT_H
#define PORTAL_OBJECT_MOVES_EVENT_H


#include "event.h"
#include "connector/connector.h"

class ObjectMovesEvent: public Event {
    uint32_t objectId;
    float xPos;
    float yPos;
public:
    ObjectMovesEvent(int objectId, float xPos, float yPos);
    ObjectMovesEvent();
    ~ObjectMovesEvent() override;
    uint32_t getId() const ;
    float getX() const;
    float getY() const;
    friend Connector &operator<<(Connector &out, const ObjectMovesEvent &c);
    friend Connector &operator>>(Connector &in, ObjectMovesEvent &c);
};


#endif //PORTAL_OBJECT_MOVES_EVENT_H
