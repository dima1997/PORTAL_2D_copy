//
// Created by franciscosicardi on 21/05/19.
//

#ifndef PORTAL_EVENT_H
#define PORTAL_EVENT_H


#include <stdint-gcc.h>
#include "protocol/protocol_code.h"
#include <connector/connector.h>

class Event {
public:
    EventType eventType;
    explicit Event(EventType eventType);
    virtual ~Event();
    /*
    PRE: Recibe un conector (Connector &) conectado.
    POST: Recibe el evento, desde el connector.
    */
    virtual void receiveFrom(Connector & in);
    /*
    PRE: Recibe un conector (Connector &) conectado.
    POST: Envia el evento, a traves del connector.
    */
    virtual void sendThrough(Connector & out) const;
    
    /*Recibe el evento desde el conector.*/
    friend Connector &operator<<(Connector &out, const Event & event);

    /*Envia el evento a traves del conector.*/
    friend Connector &operator>>(Connector &in, Event & event);
};

#endif //PORTAL_EVENT_H
