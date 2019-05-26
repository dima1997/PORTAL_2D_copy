//
// Created by franciscosicardi on 21/05/19.
//

#ifndef PORTAL_EVENT_H
#define PORTAL_EVENT_H


#include <stdint-gcc.h>
#include "protocol/protocol_code.h"

class Event {
public:
    EventType eventType;
    explicit Event(EventType eventType);
    virtual ~Event();
};


#endif //PORTAL_EVENT_H
