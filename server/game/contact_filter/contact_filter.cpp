//
// Created by franciscosicardi on 20/06/19.
//

#include "contact_filter.h"
#include "../model/body.h"
#include "../model/portal.h"
#include <Box2D/Dynamics/b2Fixture.h>

bool ContactFilter::ShouldCollide(b2Fixture *fixtureA, b2Fixture *fixtureB) {

    Body *dataA = (Body *)fixtureA->GetBody()->GetUserData();
    Body *dataB = (Body *)fixtureB->GetBody()->GetUserData();
    if (dataA && dataB && dataA->getBodyType() == ENERGY_BALL) {
        return dataB->getBodyType() != BARRIER && dataB->getBodyType() != ENERGY_EMITTER && dataB->getBodyType() != CAKE;
    }

    if (dataA && dataB && dataB->getBodyType() == ENERGY_BALL) {
        return dataA->getBodyType() != BARRIER && dataA->getBodyType() != ENERGY_EMITTER && dataA->getBodyType() != CAKE;
    }
    if (dataA && dataB && dataA->getBodyType() == PORTAL) {
        return dynamic_cast<Portal *>(dataA)->isActive();
    }
    if (dataA && dataB && dataB->getBodyType() == PORTAL) {
        return dynamic_cast<Portal *>(dataB)->isActive();
    }
    return true;
}
