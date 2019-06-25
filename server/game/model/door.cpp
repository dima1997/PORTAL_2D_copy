//
// Created by franciscosicardi on 09/06/19.
//

#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "door.h"
#include "chell.h"

Door::Door(b2World &world, float32 xPos, float32 yPos, uint32_t id,
           std::vector<std::unordered_map<uint32_t, bool>> &conditions):
           Body(world, xPos, yPos, id), Switchable(), conditions(std::move(conditions)), current(), lastStatus(false), sensor() {
    for (auto &cond_or : this->conditions) {
        std::unordered_map<uint32_t, bool> cond;
        for (auto &cond_and : cond_or) {
            cond.insert(std::make_pair(cond_and.first, false));
        }
        current.push_back(cond);
    }
    customizeBody();
}

Door::Door(const Door &other): Body(other), Switchable(other), conditions(other.conditions), current(other.current), lastStatus(other.lastStatus), sensor(other.sensor) {}

body_type_t Door::getBodyType() {
    return DOOR;
}

void Door::customizeBody() {
    b2PolygonShape door;
    door.SetAsBox(0.4f, 1.0f);
    hx = 0.4f, hy = 1.0f;
    sensor = body->CreateFixture(&door, 0.0f);
    sensor->SetSensor(false);
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

bool Door::_switchedState(bool updated) {
    bool isOpenNow = isOpen();
    sensor->SetSensor(isOpenNow);
    if (isOpenNow != lastStatus) {
        lastStatus = isOpenNow;
        if (!isOpenNow) {
            for(b2ContactEdge *contact = body->GetContactList();
                contact != nullptr;
                contact = contact->next) {
                Body *body = (Body *) contact->other->GetUserData();
                if (body->getBodyType() == CHELL) {
                    auto * chell = dynamic_cast<Chell *>(body);
                    if (chell->getXPos() > getXPos() - hx && chell->getXPos() < getXPos() + hx) {
                        chell->die();
                    }
                }
            }
        }
        return true;
    }
    return false;
}

Door::~Door() = default;
