//
// Created by franciscosicardi on 22/06/19.
//

#include <Box2D/Dynamics/b2Fixture.h>
#include "pin_tool.h"

#define PIN_TOOL_RESET_MILLIS 10000

void PinTool::createBody(float32 xPos, float32 yPos) {
    b2BodyDef bodyDef;
    bodyDef.active = false;
    bodyDef.position = b2Vec2(xPos, yPos);
    bodyDef.userData = this;
    body = world.CreateBody(&bodyDef);
}

PinTool::PinTool(b2World &world, float32 xPos, float32 yPos, uint32_t id) : Body(world, xPos, yPos, id), timer(),
                 visible(false), updated(false) {
    createBody(xPos, yPos);
}

PinTool::PinTool(const PinTool &other): Body(other), timer(), visible(false), updated(false) {}

body_type_t PinTool::getBodyType() {
    return PIN_TOOL;
}

bool PinTool::wasUpdated() {
    if (updated) {
        visible = true;
    } else if (visible && timer.GetMilliseconds() > PIN_TOOL_RESET_MILLIS) {
        visible = false;
        return true;
    }
    bool wasUpdated = updated;
    updated = false;
    return wasUpdated;
}

void PinTool::show(float32 x, float32 y) {
    moveTo(x, y);
    timer.Reset();
    if(!visible) {
        updated = true;
    }
}

PinTool::~PinTool() = default;
