//
// Created by franciscosicardi on 10/06/19.
//

#ifndef PORTAL_ROCK_H
#define PORTAL_ROCK_H


#include "movable_body.h"

class Rock: public MovableBody {
private:
    void customizeBody() override;
    float32 initialX;
    float32 initialY;
public:
    Rock(b2World &world, float32 xPos, float32 yPos, uint32_t id, float32 hy, float32 hx);
    Rock(const Rock &other);
    ~Rock() override;
    body_type_t getBodyType() override;
    void setActive(bool active);
    void moveToInitial();
};


#endif //PORTAL_ROCK_H
