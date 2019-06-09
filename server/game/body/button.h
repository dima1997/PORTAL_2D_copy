//
// Created by franciscosicardi on 09/06/19.
//

#ifndef PORTAL_BUTTON_H
#define PORTAL_BUTTON_H


#include "body.h"
#include "door.h"

class Button: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    Door *door;
public:
    Button(b2World &world, float32 xPos, float32 yPos, uint32_t id, Door *door);
    ~Button() override;
    body_type_t getBodyType() override;
};


#endif //PORTAL_BUTTON_H
