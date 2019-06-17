//
// Created by franciscosicardi on 03/06/19.
//

#include "contact_listener.h"
#include "../body/body.h"
#include "../body/portal.h"
#include "../body/cake.h"
#include "../body/chell.h"
#include "../body/button.h"
#include <Box2D/Dynamics/Contacts/b2Contact.h>

void ContactListener::BeginContact(b2Contact *contact) {
    Body *dataA = (Body *)contact->GetFixtureA()->GetBody()->GetUserData();
    Body *dataB = (Body *)contact->GetFixtureB()->GetBody()->GetUserData();
    if (contact->IsTouching() && dataA && dataB) {
        if (dataA->getBodyType() == PORTAL) {
            dataB->throughPortal = true;
            dynamic_cast<Portal *>(dataA)->startGoingThrough(dataB);
        } else if (dataA->getBodyType() == CHELL) {
            auto *chell = dynamic_cast<Chell *>(dataA);
            if (contact->GetFixtureA()->GetUserData() == (void *)CONTACT_CHECK) {
                ++chell->footContacts;
                return;
            }

            if (dataB->getBodyType() == CAKE) {
                dynamic_cast<Cake *>(dataB)->reach();
            } else if (dataB->getBodyType() == ACID_BLOCK) {
                chell->die();
            } else if (dataB->getBodyType() == BARRIER) {
                chell->throwRock(true);
            }
        } else if (dataA->getBodyType() == BUTTON) {
            auto *button = dynamic_cast<Button *>(dataA);
            if (contact->GetFixtureA()->GetUserData() == (void *)CONTACT_CHECK) {
                button->increaseContact();
            }
        } else if (dataA->getBodyType() == BARRIER) {
            if (dataB->getBodyType() == ROCK) {
                dynamic_cast<Rock *>(dataB)->moveToInitial();
            }
        }

        if (dataB->getBodyType() == PORTAL) {
            dataA->throughPortal = true;
            dynamic_cast<Portal *>(dataB)->startGoingThrough(dataA);
        }else if (dataB->getBodyType() == CHELL) {
            auto *chell = dynamic_cast<Chell *>(dataB);
            if (contact->GetFixtureB()->GetUserData() == (void *)CONTACT_CHECK) {
                ++chell->footContacts;
                return;
            }

            if (dataA->getBodyType() == CAKE) {
                dynamic_cast<Cake *>(dataA)->reach();
            } else if (dataA->getBodyType() == ACID_BLOCK) {
                chell->die();
            } else if (dataA->getBodyType() == BARRIER) {
                chell->throwRock(true);
            }
        } else if (dataB->getBodyType() == BUTTON) {
            auto *button = dynamic_cast<Button *>(dataB);
            if (contact->GetFixtureB()->GetUserData() == (void *)CONTACT_CHECK) {
                button->increaseContact();
            }
        } else if (dataB->getBodyType() == BARRIER) {
            if (dataA->getBodyType() == ROCK) {
                dynamic_cast<Rock *>(dataA)->moveToInitial();
            }
        }
    }
}

void ContactListener::EndContact(b2Contact *contact) {
    Body *dataA = (Body *)contact->GetFixtureA()->GetBody()->GetUserData();
    Body *dataB = (Body *)contact->GetFixtureB()->GetBody()->GetUserData();
    if (dataA && dataB) {
        if (dataA->getBodyType() == PORTAL) {
            dataB->throughPortal = false;
            dynamic_cast<Portal *>(dataA)->endGoingThrough();
        } else if (dataA->getBodyType() == CHELL) {
            auto *chell = dynamic_cast<Chell *>(dataA);
            if (contact->GetFixtureA()->GetUserData() == (void *)CONTACT_CHECK) {
                --chell->footContacts;
                return;
            }
        } else if (dataA->getBodyType() == BUTTON) {
            auto *button = dynamic_cast<Button *>(dataA);
            if (contact->GetFixtureA()->GetUserData() == (void *)CONTACT_CHECK) {
                button->decreaseContact();
            }
        }

        if (dataB->getBodyType() == PORTAL) {
            dataA->throughPortal = false;
            dynamic_cast<Portal *>(dataB)->endGoingThrough();
        } else if (dataB->getBodyType() == CHELL) {
            auto *chell = dynamic_cast<Chell *>(dataB);
            if (contact->GetFixtureB()->GetUserData() == (void *)CONTACT_CHECK) {
                --chell->footContacts;
                return;
            }
        } else if (dataB->getBodyType() == BUTTON) {
            auto *button = dynamic_cast<Button *>(dataB);
            if (contact->GetFixtureB()->GetUserData() == (void *)CONTACT_CHECK) {
                button->decreaseContact();
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
