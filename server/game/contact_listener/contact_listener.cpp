//
// Created by franciscosicardi on 03/06/19.
//

#include "contact_listener.h"
#include "../model/body.h"
#include "../model/portal.h"
#include "../model/cake.h"
#include "../model/chell.h"
#include "../model/button.h"
#include "../model/energy_ball.h"
#include "../../utils/geometry_utils.h"
#include "../model/energy_receiver.h"
#include <Box2D/Dynamics/Contacts/b2Contact.h>

void ContactListener::BeginContact(b2Contact *contact) {
    Body *dataA = (Body *)contact->GetFixtureA()->GetBody()->GetUserData();
    Body *dataB = (Body *)contact->GetFixtureB()->GetBody()->GetUserData();
    if (contact->IsTouching() && dataA && dataB) {
        if (dataA->getBodyType() == PORTAL) {
            dynamic_cast<Portal *>(dataA)->startGoingThrough(dataB);
            if (dataB ->getBodyType() == CHELL) {
                dynamic_cast<Chell *>(dataB)->throughPortal = true;
                return;
            }
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
                chell->throwRock(THROW_INITIAL);
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
        } else if (dataA->getBodyType() == ENERGY_BALL) {
            auto *ball = dynamic_cast<EnergyBall *>(dataA);
            if (dataB->getBodyType() == ENERGY_RECEIVER) {
                ball->resetPosition();
                dynamic_cast<EnergyReceiver *>(dataB)->updateActive();
            } else {
                b2WorldManifold worldManifold;
                contact->GetWorldManifold(&worldManifold);
                const b2Vec2 vec2 = ball->getDirection();
                const b2Vec2 vec3 = -vec2;
                ball->setDirection(normal_reflection(vec3, worldManifold.normal));
            }
        }

        if (dataB->getBodyType() == PORTAL) {
            dynamic_cast<Portal *>(dataB)->startGoingThrough(dataA);
            if (dataA ->getBodyType() == CHELL) {
                dynamic_cast<Chell *>(dataA)->throughPortal = true;
                return;
            }
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
                chell->throwRock(THROW_INITIAL);
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
        } else if (dataB->getBodyType() == ENERGY_BALL) {
            auto *ball = dynamic_cast<EnergyBall *>(dataB);
            if (dataA->getBodyType() == ENERGY_RECEIVER) {
                ball->resetPosition();
                dynamic_cast<EnergyReceiver *>(dataA)->updateActive();
            } else {
                b2WorldManifold worldManifold;
                contact->GetWorldManifold(&worldManifold);
                const b2Vec2 vec2 = ball->getDirection();
                const b2Vec2 vec3 = -vec2;
                ball->setDirection(normal_reflection(vec3, worldManifold.normal));
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
            if (dataB ->getBodyType() == CHELL) {
                dynamic_cast<Chell *>(dataB)->throughPortal = false;
                return;
            }
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
            dynamic_cast<Portal *>(dataB)->endGoingThrough();
            if (dataA ->getBodyType() == CHELL) {
                dynamic_cast<Chell *>(dataA)->throughPortal = false;
                return;
            }        } else if (dataB->getBodyType() == CHELL) {
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
