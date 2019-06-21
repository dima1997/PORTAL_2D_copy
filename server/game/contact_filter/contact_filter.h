//
// Created by franciscosicardi on 20/06/19.
//

#ifndef PORTAL_CONTACT_FILTER_H
#define PORTAL_CONTACT_FILTER_H


#include <Box2D/Dynamics/b2WorldCallbacks.h>

class ContactFilter: public b2ContactFilter {
    bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;
};


#endif //PORTAL_CONTACT_FILTER_H
