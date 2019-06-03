//
// Created by franciscosicardi on 03/06/19.
//

#include "portal_contact_listener.h"
#include "../body/body.h"
#include "../body/portal.h"
#include <Box2D/Dynamics/Contacts/b2Contact.h>

void PortalContactListener::BeginContact(b2Contact *contact) {
    Body *dataA = (Body *)contact->GetFixtureA()->GetBody()->GetUserData();
    Body *dataB = (Body *)contact->GetFixtureB()->GetBody()->GetUserData();
    Portal *portal;
    if (dataA && dataB) {
        if (dataA->getBodyType() == PORTAL) {
            portal = dynamic_cast<Portal *>(dataA);
            portal->startGoingThrough(dataB);
        } else if (dataB->getBodyType() == PORTAL) {
            portal = dynamic_cast<Portal *>(dataB);
            portal->startGoingThrough(dataA);
        }
    }
}

void PortalContactListener::EndContact(b2Contact *contact) {
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
