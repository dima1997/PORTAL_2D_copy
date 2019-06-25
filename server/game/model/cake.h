//
// Created by franciscosicardi on 03/06/19.
//

#ifndef PORTAL_CAKE_H
#define PORTAL_CAKE_H


#include "body.h"
#include "switchable.h"

class Cake: public Body, public Switchable {
private:
    void customizeBody() override;
    int reachedNumber;
public:
    Cake(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    Cake(const Cake &other);
    ~Cake() override;
    body_type_t getBodyType() override;
    void reach();
    bool wasReached();
};


#endif //PORTAL_CAKE_H
