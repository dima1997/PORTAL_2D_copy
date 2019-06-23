//
// Created by franciscosicardi on 17/06/19.
//

#ifndef PORTAL_BARRIER_H
#define PORTAL_BARRIER_H


#include "body.h"

class Barrier: public Body {
private:
    void customizeBody() override;
public:
    Barrier(b2World &world, float32 xPos, float32 yPos, uint32_t id, float32 hy, float32 hx);
    Barrier(const Barrier &other);
    ~Barrier() override;
    body_type_t getBodyType() override;
};


#endif //PORTAL_BARRIER_H
