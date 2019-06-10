//
// Created by franciscosicardi on 10/06/19.
//

#include "grab_rock_event.h"

GrabRockEvent::GrabRockEvent(uint32_t chellId, uint32_t rockId):
                             Event(grab_rock), chellId(chellId), rockId(rockId) {}

uint32_t GrabRockEvent::getChellId() const {
    return chellId;
}

uint32_t GrabRockEvent::getRockId() const {
    return rockId;
}

void GrabRockEvent::receiveFrom(Connector &in) {
    in >> this->chellId >> this->rockId;
}

void GrabRockEvent::sendThrough(Connector &out) const {
    out << (uint8_t) this->eventType << this->chellId << this->rockId;
}

GrabRockEvent::~GrabRockEvent() = default;
