//
// Created by franciscosicardi on 02/06/19.
//

#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include "portal.h"
#include "../../utils/geometry_utils.h"

Portal::Portal(b2World &world, float32 xPos, float32 yPos, uint32_t id):
               MovableBody(world, xPos, yPos, id), other(), usable(false), visible(false), normal(0, 1) {
    customizeBody();
}

Portal::Portal(const Portal &other): MovableBody(other), other(other.other), usable(other.usable), visible(other.visible),
                                     normal(other.normal) {
    if (this->other) {
        this->other->other = this;
    }
}

void connect(Portal &portal1, Portal &portal2) {
    portal1.other = &portal2;
    portal2.other = &portal1;
}

void Portal::customizeBody() {
    body->SetType(b2_staticBody);
    b2Vec2 direction = b2Vec2(-normal.y, normal.x);
    direction.Normalize();
    b2EdgeShape edgeShape;
    edgeShape.Set(-0.5f * direction, 0.5f * direction);
    b2FixtureDef edgeFixtureDef;
    edgeFixtureDef.shape = &edgeShape;
    body->CreateFixture(&edgeFixtureDef);
}

void Portal::startGoingThrough(MovableBody *body) {
    if (!usable)
        return;
    body->moveTo(other->getXPos() + (body->hx * other->normal.x), other->getYPos() + (body->hy * other->normal.y));
    float32 angle = angle_between_vectors(normal, -other->normal);
    b2Vec2 newDirection = rotate_vector_counterclockwise(angle, body->getCurrentVelocity());
    body->applyImpulse(newDirection.x, newDirection.y);
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
    b2Vec2 direction = b2Vec2(-normal.y, normal.x);
    direction.Normalize();
    ((b2EdgeShape *)(body->GetFixtureList()->GetShape()))->Set(-0.5f * direction, 0.5f * direction);
}

void Portal::showAndActivateIfRequires() {
    if (!visible) {
        visible = true;
        switchState();
        if (other->visible) {
            this->usable = true;
            other->usable = true;
        }
    }
}

void Portal::hideAndDeactivate() {
    if (visible) {
        switchState();
    }
    visible = false;
    usable = false;
}

float32 Portal::getNormalX() {
    return normal.x;
}

float32 Portal::getNormalY() {
    return normal.y;
}

Portal::~Portal() = default;

