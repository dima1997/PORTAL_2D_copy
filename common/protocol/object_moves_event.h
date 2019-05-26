//
// Created by franciscosicardi on 21/05/19.
//

#ifndef PORTAL_OBJECT_MOVES_EVENT_H
#define PORTAL_OBJECT_MOVES_EVENT_H


#include "event.h"
#include "../connector/connector.h"

class ObjectMovesEvent: public Event {
    uint32_t objectId;
    float xPos;
    float yPos;
public:
    ObjectMovesEvent(int objectId, float xPos, float yPos);
    ~ObjectMovesEvent() override;
    uint32_t getId() const ;
    float getX() const;
    float getY() const;
    friend Connector &operator<<(Connector &out, 
                                    const ObjectMovesEvent &event);
    friend Connector &operator>>(Connector &out, ObjectMovesEvent &event);
};


#endif //PORTAL_OBJECT_MOVES_EVENT_H
