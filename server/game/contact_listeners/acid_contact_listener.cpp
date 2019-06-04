//
// Created by franciscosicardi on 03/06/19.
//

#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "../body/body.h"
#include "acid_contact_listener.h"
#include "../body/chell.h"

void AcidContactListener::BeginContact(b2Contact *contact) {
    Body *dataA = (Body *)contact->GetFixtureA()->GetBody()->GetUserData();
    Body *dataB = (Body *)contact->GetFixtureB()->GetBody()->GetUserData();
    Chell *chell;
    if (dataA && dataB) {
        if (dataA->getBodyType() == ACID_BLOCK && dataB->getBodyType() == CHELL) {
            chell = dynamic_cast<Chell *>(dataB);
        } else if (dataB->getBodyType() == CAKE && dataA->getBodyType() == ACID_BLOCK) {
            chell = dynamic_cast<Chell *>(dataA);
        } else {
            return;
        }
        chell->die();
    }
}
