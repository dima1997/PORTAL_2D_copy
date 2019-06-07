//
// Created by franciscosicardi on 06/06/19.
//

#include "portal_ray_cast_callback.h"

PortalRaycastCallback::PortalRaycastCallback(): lastFixture(), point(), normal() {}

float32 PortalRaycastCallback::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) {
    lastFixture = fixture;
    this->point = b2Vec2(point);
    this->normal = b2Vec2(normal);
    return fraction;
}

b2Fixture *PortalRaycastCallback::getFixture() {
    return lastFixture;
}

b2Vec2 PortalRaycastCallback::getPoint() {
    return point;
}

b2Vec2 PortalRaycastCallback::getNormal() {
    return normal;
}
