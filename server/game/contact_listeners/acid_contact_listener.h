//
// Created by franciscosicardi on 03/06/19.
//

#ifndef PORTAL_ACID_CONTACT_LISTENER_H
#define PORTAL_ACID_CONTACT_LISTENER_H


#include <Box2D/Dynamics/b2WorldCallbacks.h>

class AcidContactListener: public b2ContactListener {
    void BeginContact(b2Contact* contact) override;
};


#endif //PORTAL_ACID_CONTACT_LISTENER_H
