#include "portal_moves_event.h"

#include "object_moves_event.h"
#include "protocol/protocol_code.h"

PortalMovesEvent::PortalMovesEvent(
    int objectId, 
    float xPos, 
    float yPos, 
    uint32_t chellId,
    float normalX,
    float normalY
)
:   ObjectMovesEvent(objectId, xPos, yPos, portal_moves),
    chellId(chellId), normalX(normalX), normalY(normalY) {}

PortalMovesEvent::PortalMovesEvent()
:   ObjectMovesEvent(0,0,0,portal_moves),
    chellId(0), normalX(0), normalY(0) {}

PortalMovesEvent::~PortalMovesEvent() = default;

/*
PRE: Recibe un conector (Connector &) conectado.
POST: Recibe el evento, desde el connector.
*/
void PortalMovesEvent::receiveFrom(Connector & in) {
    // El event type se recibe por afuera.
    in >> this->objectId;
    in >> this->xPos;
    in >> this->yPos;
    in >> this->chellId;
    in >> this->normalX;
    in >> this->normalY;
}

/*
PRE: Recibe un conector (Connector &) conectado.
POST: Envia el evento, a traves del connector.
*/
void PortalMovesEvent::sendThrough(Connector & out) const {
    out << (uint8_t) this->eventType << (uint32_t) objectId;
    out << this->xPos << this->yPos << this->chellId << this->normalX << this->normalY;
}

uint32_t PortalMovesEvent::get_chell_id(){
    return this->chellId;
}

float PortalMovesEvent::get_normal_x(){
    return this->normalX;
}

float PortalMovesEvent::get_normal_y(){
    return this->normalY;
}