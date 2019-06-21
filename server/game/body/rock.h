//
// Created by franciscosicardi on 10/06/19.
//

#ifndef PORTAL_ROCK_H
#define PORTAL_ROCK_H


#include "body.h"

class Rock: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    float32 initialX;
    float32 initialY;
public:
    Rock(b2World &world, float32 xPos, float32 yPos, uint32_t id, float32 hy, float32 hx);
    Rock(Rock &&other) noexcept;
    ~Rock() override;
    body_type_t getBodyType() override;
    void setActive(bool active);
    void moveToInitial();
};


#endif //PORTAL_ROCK_H
