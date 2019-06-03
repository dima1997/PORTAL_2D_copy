//
// Created by franciscosicardi on 03/06/19.
//

#ifndef PORTAL_PORTAL_CONTACT_LISTENER_H
#define PORTAL_PORTAL_CONTACT_LISTENER_H


#include <Box2D/Dynamics/b2WorldCallbacks.h>

class PortalContactListener: public b2ContactListener {

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
};


#endif //PORTAL_PORTAL_CONTACT_LISTENER_H
