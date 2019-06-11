//
// Created by franciscosicardi on 21/05/19.
//

#include "event.h"
#include <connector/connector.h>

Event::Event(EventType eventType): eventType(eventType) {}

Event::~Event() = default;

/*
PRE: Recibe un conector (Connector &) conectado.
POST: Recibe el evento, desde el connector.
*/
void Event::receiveFrom(Connector & in){
    uint8_t eventTypeExplicit;
    in >> eventTypeExplicit;
    this->eventType = (EventType) eventTypeExplicit;
}
/*
PRE: Recibe un conector (Connector &) conectado.
POST: Envia el evento, a traves del connector.
*/
void Event::sendThrough(Connector & out) const{
    auto eventTypeExplicit = (uint8_t) this->eventType;
    out << eventTypeExplicit;
}

/*Recibe el evento desde el conector.*/
Connector &operator<<(Connector &out, const Event & event) {
    event.sendThrough(out);
    return out;
}

/*Envia el evento a traves del conector.*/
Connector &operator>>(Connector &in, Event & event) {
    event.receiveFrom(in);
    return in;
}