//
// Created by franciscosicardi on 09/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "door.h"

Door::Door(b2World &world, float32 xPos, float32 yPos, uint32_t id,
           std::vector<std::unordered_map<uint32_t, bool>> &conditions):
           Body(world, xPos, yPos, id), conditions(std::move(conditions)), current(), lastStatus(false) {
    for (auto &cond_or : this->conditions) {
        std::unordered_map<uint32_t, bool> cond;
        for (auto &cond_and : cond_or) {
            cond.insert(std::make_pair(cond_and.first, false));
        }
        current.push_back(cond);
    }
    customizeBody();
}

Door::Door(const Door &other): Body(other), conditions(other.conditions), current(other.current), lastStatus(other.lastStatus) {}

body_type_t Door::getBodyType() {
    return DOOR;
}

void Door::customizeBody() {
    b2PolygonShape door;
    door.SetAsBox(0.4f, 1.0f);

    body->CreateFixture(&door, 0.0f);
}

bool Door::isOpen() {
    for (int i = 0; i < current.size(); ++i) {
        bool open = true;
        for (auto &cond : conditions.at(i)) {
            if (cond.second != current.at(i).at(cond.first)) {
                open = false;
            }
        }
        if (open) return true;
    }
    return false;
}

void Door::updateConditionStatus(uint32_t id) {
    for (auto &cond_or : current) {
        if (cond_or.count(id) > 0) {
            cond_or[id] = !cond_or[id];
        }
    }
}

bool Door::update() {
    bool isOpenNow = isOpen();
    body->SetActive(!isOpenNow);
    if (isOpenNow != lastStatus) {
        lastStatus = isOpenNow;
        return true;
    }
    return false;
}

Door::~Door() = default;
