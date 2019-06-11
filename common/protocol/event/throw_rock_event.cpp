//
// Created by franciscosicardi on 10/06/19.
//

#include "throw_rock_event.h"

ThrowRockEvent::ThrowRockEvent(uint32_t rockId):
                               Event(throw_rock), rockId(rockId) {}

uint32_t ThrowRockEvent::getRockId() const {
    return rockId;
}

void ThrowRockEvent::receiveFrom(Connector &in) {
    in >> this->rockId;
}

void ThrowRockEvent::sendThrough(Connector &out) const {
    out << (uint8_t) this->eventType << this->rockId;
}

ThrowRockEvent::~ThrowRockEvent() = default;
