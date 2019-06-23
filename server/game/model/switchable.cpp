//
// Created by franciscosicardi on 23/06/19.
//

#include "switchable.h"

Switchable::Switchable(bool initState): updated(initState) {}

Switchable::Switchable(const Switchable &other): updated(other.updated) {}

bool Switchable::wasUpdated() {
    return _wasUpdated();
}

bool Switchable::_wasUpdated() {
    bool wasUpdated = updated;
    updated = false;
    return wasUpdated;
}

Switchable::~Switchable() = default;
