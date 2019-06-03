//
// Created by franciscosicardi on 03/06/19.
//

#ifndef PORTAL_CAKE_H
#define PORTAL_CAKE_H


#include "body.h"

class Cake: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    bool reached;
public:
    Cake(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    ~Cake() override;
    body_type_t getBodyType() override;
    void reach();
    bool wasReached();
};


#endif //PORTAL_CAKE_H
