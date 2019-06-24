//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_MOVABLE_BODY_H
#define PORTAL_MOVABLE_BODY_H


#include "body.h"

class MovableBody: public Body {
private:
    bool updated_position;
    virtual bool _changedPosition();
    virtual void _moveTo(float32 x, float32 y);
protected:
    virtual void _applyImpulse(float32 xSpeed, float32 ySpeed);
public:
    MovableBody(b2World &world, float32 xPos, float32 yPos, uint32_t id);
    MovableBody(const MovableBody &other);
    ~MovableBody() override;
    void moveTo(float32 x, float32 y);
    bool changedPosition();
    void applyImpulse(float32 xSpeed, float32 ySpeed);
    b2Vec2 getCurrentVelocity();
};


#endif //PORTAL_MOVABLE_BODY_H
