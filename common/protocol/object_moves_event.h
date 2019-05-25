//
// Created by franciscosicardi on 21/05/19.
//

#ifndef PORTAL_OBJECT_MOVES_EVENT_H
#define PORTAL_OBJECT_MOVES_EVENT_H


#include <Box2D/Common/b2Settings.h>
#include "event.h"
#include "../connector.h"

class ObjectMovesEvent: public Event {
private:
    int objectId;
    float32 xPos;
    float32 yPos;
public:
    ObjectMovesEvent(int objectId, float32 xPos, float32 yPos);
    ~ObjectMovesEvent() override;
    friend Connector &operator<<(Connector &out, const ObjectMovesEvent &c);
};


#endif //PORTAL_OBJECT_MOVES_EVENT_H
