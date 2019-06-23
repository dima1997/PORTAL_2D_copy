//
// Created by franciscosicardi on 23/06/19.
//

#include "switchable.h"

Switchable::Switchable(): updated(false) {}

Switchable::Switchable(const Switchable &other): updated(other.updated) {}

bool Switchable::switchedState() {
    return _switchedState();
}

bool Switchable::_switchedState() {
    bool wasUpdated = updated;
    updated = false;
    return wasUpdated;
}

void Switchable::switchState() {
    updated = true;
    _switchState();
}

void Switchable::_switchState() {}

Switchable::~Switchable() = default;
