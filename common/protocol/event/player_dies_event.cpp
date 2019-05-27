//
// Created by franciscosicardi on 26/05/19.
//

#include "player_dies_event.h"

PlayerDiesEvent::PlayerDiesEvent(): Event(player_wins) {}

Connector &operator<<(Connector &out, const PlayerDiesEvent &c) {
    return out << (uint8_t) c.eventType;
}

PlayerDiesEvent::~PlayerDiesEvent() = default;
