//
// Created by franciscosicardi on 02/06/19.
//

#ifndef PORTAL_PORTAL_H
#define PORTAL_PORTAL_H


#include "body.h"

class Portal: public Body {
private:
    Portal *other;
    void createBody(float32 xPos, float32 yPos) override;
public:
    Portal(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    ~Portal() override;
    friend void connect(Portal *portal1, Portal *portal2);
    void moveTo(float32 x, float32 y);
};


#endif //PORTAL_PORTAL_H
