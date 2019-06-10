//
// Created by franciscosicardi on 06/06/19.
//

#ifndef PORTAL_PORTALRAYCASTCALLBACK_H
#define PORTAL_PORTALRAYCASTCALLBACK_H


#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Common/b2Math.h>
#include "../body/chell.h"

class PortalRaycastCallback: public b2RayCastCallback {
private:
    Chell * chell;
    b2Fixture *lastFixture;
    b2Vec2 point;
    b2Vec2 normal;
public:
    explicit PortalRaycastCallback(Chell *chell);
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                          const b2Vec2& normal, float32 fraction) override;
    b2Fixture *getFixture();
    b2Vec2 getPoint();
    b2Vec2 getNormal();
};


#endif //PORTAL_PORTALRAYCASTCALLBACK_H
