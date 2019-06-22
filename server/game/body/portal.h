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
    bool usable;
    b2Vec2 normal;
public:
    Portal(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    Portal(const Portal &other);
    ~Portal() override;
    void startGoingThrough(Body *body);
    void endGoingThrough();
    friend void connect(Portal &portal1, Portal &portal2);
    body_type_t getBodyType() override;
    void setNormal(b2Vec2 normal);
};


#endif //PORTAL_PORTAL_H
