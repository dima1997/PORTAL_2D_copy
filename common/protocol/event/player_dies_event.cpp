//
// Created by franciscosicardi on 26/05/19.
//

#include "player_dies_event.h"

PlayerDiesEvent::PlayerDiesEvent(uint32_t id): Event(player_dies), id(id) {}

Connector &operator<<(Connector &out, const PlayerDiesEvent &c) {
//    return out << (uint8_t) c.eventType << c.id;
    return out << (uint8_t) c.eventType;
}

PlayerDiesEvent::~PlayerDiesEvent() = default;
