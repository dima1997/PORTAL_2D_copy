//
// Created by franciscosicardi on 21/05/19.
//

#ifndef PORTAL_MOVES_EVENT_H
#define PORTAL_MOVES_EVENT_H

#include "object_moves_event.h"
#include "event.h"
#include <connector/connector.h>

class PortalMovesEvent: public ObjectMovesEvent {
protected:
    uint32_t chellId;
    float normalX;
    float normalY;
public:
    PortalMovesEvent(int objectId, float xPos, float yPos, uint32_t chellId, float normalX, float normalY);
    PortalMovesEvent();
    ~PortalMovesEvent() override;
    /*
    PRE: Recibe un conector (Connector &) conectado.
    POST: Recibe el evento, desde el connector.
    */
    void receiveFrom(Connector & in) override;
    /*
    PRE: Recibe un conector (Connector &) conectado.
    POST: Envia el evento, a traves del connector.
    */
    void sendThrough(Connector & out) const override;


    uint32_t get_chell_id();
};


#endif // PORTAL_MOVES_EVENT_H
