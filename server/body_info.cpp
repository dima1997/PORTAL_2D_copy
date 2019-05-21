//
// Created by franciscosicardi on 19/05/19.
//

#include "body_info.h"

BodyInfo::BodyInfo(unsigned int id, b2Vec2 position):
           id(id), position(position), updated(false) {}

bool BodyInfo::isUpdated() {
    return updated;
}

void BodyInfo::update(b2Vec2 pos) {
    if (position.x != pos.x || position.y != pos.y) {
        position = pos;
        updated = true;
    } else {
        updated = false;
    }
}

b2Vec2 BodyInfo::getPosition() {
    return position;
}

BodyInfo::~BodyInfo() = default;


