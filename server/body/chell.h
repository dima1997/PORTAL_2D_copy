//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_CHELL_H
#define PORTAL_CHELL_H


#include "body.h"

class Chell: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    uint8_t playerId;
public:
    Chell(uint32_t id, b2World &world, float32 xPos, float32 yPos, uint8_t playerId);
    ~Chell() override;

};


#endif //PORTAL_CHELL_H
