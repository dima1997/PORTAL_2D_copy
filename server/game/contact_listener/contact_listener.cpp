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
        if (dataA->getBodyType() == PORTAL) {
            dynamic_cast<Portal *>(dataA)->startGoingThrough(dataB);
        } else if (dataB->getBodyType() == PORTAL) {
            dynamic_cast<Portal *>(dataB)->startGoingThrough(dataA);
        } else if (dataA->getBodyType() == CHELL) {
            auto *chell = dynamic_cast<Chell *>(dataA);
            if (contact->GetFixtureA()->GetUserData() == (void *)GROUND_CHECK) {
                ++chell->footContacts;
            }

            if (dataB->getBodyType() == CAKE) {
                dynamic_cast<Cake *>(dataB)->reach();
            } else if (dataB->getBodyType() == ACID_BLOCK) {
                chell->die();
            }

        } else if (dataB->getBodyType() == CHELL) {
            auto *chell = dynamic_cast<Chell *>(dataB);
            if (contact->GetFixtureB()->GetUserData() == (void *)GROUND_CHECK) {
                ++chell->footContacts;
            }

            if (dataA->getBodyType() == CAKE) {
                dynamic_cast<Cake *>(dataA)->reach();
            } else if (dataA->getBodyType() == ACID_BLOCK) {
                chell->die();
            }
        }
    }
}

void ContactListener::EndContact(b2Contact *contact) {
    Body *dataA = (Body *)contact->GetFixtureA()->GetBody()->GetUserData();
    Body *dataB = (Body *)contact->GetFixtureB()->GetBody()->GetUserData();
    if (dataA && dataB) {
        if (dataA->getBodyType() == PORTAL) {
            dynamic_cast<Portal *>(dataA)->endGoingThrough();
        } else if (dataB->getBodyType() == PORTAL) {
            dynamic_cast<Portal *>(dataB)->endGoingThrough();
        } else if (dataA->getBodyType() == CHELL) {
            auto *chell = dynamic_cast<Chell *>(dataA);
            if (contact->GetFixtureA()->GetUserData() == (void *)GROUND_CHECK) {
                --chell->footContacts;
            }
        } else if (dataB->getBodyType() == CHELL) {
            auto *chell = dynamic_cast<Chell *>(dataB);
            if (contact->GetFixtureB()->GetUserData() == (void *)GROUND_CHECK) {
                --chell->footContacts;
            }
        }
    }
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
    Body *dataA = (Body *)contact->GetFixtureA()->GetBody()->GetUserData();
    Body *dataB = (Body *)contact->GetFixtureB()->GetBody()->GetUserData();
    if (dataA && dataB) {
        if (dataA->getBodyType() == PORTAL) {
            contact->SetEnabled(false);
        } else if (dataB->getBodyType() == PORTAL) {
            contact->SetEnabled(false);
        }
    }
}
