//
// Created by franciscosicardi on 09/06/19.
//

#include "button.h"

Button::Button(b2World &world, float32 xPos, float32 yPos, uint32_t id, Door *door):
               Body(world, xPos, yPos, id), door(door) {}

body_type_t Button::getBodyType() {
    return BUTTON;
}

void Button::createBody(float32 xPos, float32 yPos) {

}

Button::~Button() = default;
