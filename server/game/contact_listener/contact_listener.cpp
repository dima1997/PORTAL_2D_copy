//
// Created by franciscosicardi on 03/06/19.
//

#include "contact_listener.h"
#include "../body/body.h"
#include "../body/portal.h"
#include "../body/cake.h"
#include "../body/chell.h"
#include <Box2D/Dynamics/Contacts/b2Contact.h>

void ContactListener::BeginContact(b2Contact *contact) {

    Body *dataA = (Body *)contact->GetFixtureA()->GetBody()->GetUserData();
    Body *dataB = (Body *)contact->GetFixtureB()->GetBody()->GetUserData();
    if (contact->IsTouching() && dataA && dataB) {
        if (dataA->getBodyType() == CAKE && dataB->getBodyType() == CHELL) {
            dynamic_cast<Cake *>(dataA)->reach();
        } else if (dataB->getBodyType() == CAKE && dataA->getBodyType() == CHELL) {
            dynamic_cast<Cake *>(dataB)->reach();
        } else if (dataA->getBodyType() == PORTAL) {
            dynamic_cast<Portal *>(dataA)->startGoingThrough(dataB);
        } else if (dataB->getBodyType() == PORTAL) {
            dynamic_cast<Portal *>(dataB)->startGoingThrough(dataA);
        } else if (dataA->getBodyType() == ACID_BLOCK && dataB->getBodyType() == CHELL) {
            dynamic_cast<Chell *>(dataB)->die();
        } else if (dataB->getBodyType() == CAKE && dataA->getBodyType() == ACID_BLOCK) {
            dynamic_cast<Chell *>(dataA)->die();
        }
    }
}

void ContactListener::EndContact(b2Contact *contact) {
    Body *dataA = (Body *)contact->GetFixtureA()->GetBody()->GetUserData();
    Body *dataB = (Body *)contact->GetFixtureB()->GetBody()->GetUserData();
    Portal *portal;
    if (dataA && dataB) {
        if (dataA->getBodyType() == PORTAL) {
            portal = dynamic_cast<Portal *>(dataA);
            portal->endGoingThrough();
        } else if (dataB->getBodyType() == PORTAL) {
            portal = dynamic_cast<Portal *>(dataB);
            portal->endGoingThrough();
        }
    }
}
