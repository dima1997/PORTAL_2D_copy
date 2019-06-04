//
// Created by franciscosicardi on 26/05/19.
//

#include "player_dies_event.h"

PlayerDiesEvent::PlayerDiesEvent(uint32_t id): Event(player_dies), id(id) {}

/*
PRE: Recibe un conector (Connector &) conectado.
POST: Envia el evento: evento + id, a traves del connector.
*/
void PlayerDiesEvent::sendThrough(Connector & out) const {
    out << (uint8_t) this->eventType << this->id;
}

// Esta funcion no sirve, pues el evento es interpretado como un Event
Connector &operator<<(Connector &out, const PlayerDiesEvent &c) {
    return out << (uint8_t) c.eventType << c.id;
//    return out << (uint8_t) c.eventType;
}

PlayerDiesEvent::~PlayerDiesEvent() = default;
