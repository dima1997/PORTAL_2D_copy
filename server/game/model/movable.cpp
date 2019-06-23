//
// Created by franciscosicardi on 23/06/19.
//

#include "movable.h"

bool Movable::changedPosition() {
    return _changedPosition();
}

Movable::Movable(float32 xPos, float32 yPos): xPos(xPos), yPos(yPos) {}

Movable::Movable(const Movable &other): xPos(other.xPos), yPos(other.yPos) {}

void Movable::moveTo(float32 x, float32 y) {
    xPos = x;
    yPos = y;
    _moveTo(x, y);
}

Movable::~Movable() = default;
