//
// Created by franciscosicardi on 03/06/19.
//

#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "cake_contact_listener.h"
#include "../body/body.h"
#include "../body/cake.h"

void CakeContactListener::BeginContact(b2Contact *contact) {
    Body *dataA = (Body *)contact->GetFixtureA()->GetBody()->GetUserData();
    Body *dataB = (Body *)contact->GetFixtureB()->GetBody()->GetUserData();
    Cake *cake;
    if (dataA && dataB) {
        if (dataA->getBodyType() == CAKE && dataB->getBodyType() == CHELL) {
            cake = dynamic_cast<Cake *>(dataA);
        } else if (dataB->getBodyType() == CAKE && dataA->getBodyType() == CHELL) {
            cake = dynamic_cast<Cake *>(dataB);
        } else {
            return;
        }
        cake->reach();
    }
}
