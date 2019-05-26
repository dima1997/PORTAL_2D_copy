//
// Created by franciscosicardi on 26/05/19.
//

#include "player_wins_event.h"

PlayerWinsEvent::PlayerWinsEvent(): Event(player_wins) {}

Connector &operator<<(Connector &out, const PlayerWinsEvent &c) {
    return out << (uint8_t) c.eventType;
}

PlayerWinsEvent::~PlayerWinsEvent() = default;
