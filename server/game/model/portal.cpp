//
// Created by franciscosicardi on 02/06/19.
//

#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include "portal.h"

Portal::Portal(b2World &world, float32 xPos, float32 yPos, uint32_t id):
               Body(world, xPos, yPos, id), other(), usable(false), visible(false), changeVisibility(false), normal(0, 1) {
    createBody(xPos, yPos);
}

Portal::Portal(const Portal &other): Body(other), other(other.other), usable(other.usable), visible(other.visible),
                                     changeVisibility(false), normal(other.normal) {
    if (this->other) {
        this->other->other = this;
    }
}

void connect(Portal &portal1, Portal &portal2) {
    portal1.other = &portal2;
    portal2.other = &portal1;
}

void Portal::createBody(float32 xPos, float32 yPos) {
    if (body) {
        world.DestroyBody(body);
    }
    b2BodyDef bodyDef;
    bodyDef.position.Set(xPos, yPos);
    body = world.CreateBody(&bodyDef);
    body->SetUserData(this);

    b2Vec2 direction = b2Vec2(-normal.y, normal.x);
    direction.Normalize();
    b2EdgeShape edgeShape;
    edgeShape.Set(-0.5f * direction, 0.5f * direction);
    b2FixtureDef edgeFixtureDef;
    edgeFixtureDef.shape = &edgeShape;
    body->CreateFixture(&edgeFixtureDef);
}

void Portal::startGoingThrough(Body *body) {
    if (!usable)
        return;
    body->moveTo(other->getXPos() + (body->hx * other->normal.x), other->getYPos() + (body->hy * other->normal.y));

    float32 angle = acosf(b2Dot(this->normal, -other->normal)/(this->normal.Length() * other->normal.Length()));
    float32 cs = cosf(angle);
    float32 sn = sinf(angle);

    b2Vec2 currentVel = body->getCurrentVelocity();

    float32 newX = currentVel.x * cs - currentVel.y * sn;
    float32 newY = currentVel.x * sn + currentVel.y * cs;
    body->applyImpulse(newX, newY);
    other->usable = false;
}

body_type_t Portal::getBodyType() {
    return PORTAL;
}

void Portal::endGoingThrough() {
    if (visible && other->visible) {
        usable = true;
    }
}

void Portal::setNormal(b2Vec2 normal) {
    this->normal = normal;
    createBody(this->getXPos(), this->getYPos());
}

void Portal::showAndActivateIfRequires() {
    if (!visible) {
        visible = true;
        changeVisibility = true;
        if (other->visible) {
            this->usable = true;
            other->usable = true;
        }
    }
}

void Portal::hideAndDeactivate() {
    if (visible) {
        changeVisibility = true;
    }
    visible = false;
    usable = false;
}

bool Portal::changedVisivility() {
    bool changed = changeVisibility;
    changeVisibility = false;
    return changed;
}

float32 Portal::getNormalX() {
    return normal.x;
}

float32 Portal::getNormalY() {
    return normal.y;
}

Portal::~Portal() = default;
