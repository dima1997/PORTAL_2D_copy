//
// Created by franciscosicardi on 02/06/19.
//

#ifndef PORTAL_PORTAL_H
#define PORTAL_PORTAL_H


#include "movable_body.h"
#include "switchable.h"

class Portal: public MovableBody, public Switchable {
private:
    Portal *other;
    void customizeBody() override;
    bool usable;
    bool visible;
    b2Vec2 normal;
public:
    Portal(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    Portal(const Portal &other);
    ~Portal() override;
    void startGoingThrough(MovableBody *body);
    void endGoingThrough();
    friend void connect(Portal &portal1, Portal &portal2);
    body_type_t getBodyType() override;
    void setNormal(b2Vec2 normal);
    void showAndActivateIfRequires();
    void hideAndDeactivate();
    float32 getNormalX();
    float32 getNormalY();
};


#endif //PORTAL_PORTAL_H
