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

PlayerDiesEvent::~PlayerDiesEvent() = default;
